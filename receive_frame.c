#include <stdint.h>
#include <stdio.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include "receive_frame.h"
#include <netinet/if_ether.h>
long long time1_sec = 0;
long long time1_usec = 0;  
long long time2_sec = 0;
long long time2_usec = 0;  

char errbuff[PCAP_ERRBUF_SIZE];
char* interface_name;
pcap_t* handler;
struct bpf_program fp;
bpf_u_int32 interface_ip;
bpf_u_int32 interface_mask;
struct pcap_pkthdr packet_info;
/*this function initalizes the pcap library by specifying the network device to track*/
void libpcap_init(void)
{
    interface_name = pcap_lookupdev(errbuff);
    printf("The name of the interface is:%s\n",interface_name);
    if (interface_name == NULL)
    {
        printf("Error in interface selection\n");
        printf("The reason of the error is :%s",errbuff);
    }
     int32_t res = pcap_lookupnet(interface_name,&interface_ip,&interface_mask,errbuff);
     if (res == -1)
    {
        printf("Error in determining interface ip and mask\n");
        printf("The reason of the error is :%s",errbuff);

    }
    //initialize libpcap session
     handler =  pcap_open_live(interface_name ,MAX_PACKET_SIZE ,TURN_OFF_PROMISCUOUS_MODE ,WAIT_UNTIL_COPIED_MS,errbuff);
    if (handler == NULL)
    {
        printf("Error in initializing libpcap session\n");
        printf("The reason of the error is :%s",errbuff);

    }

}



/*this is optional it takes a string (this string have specific format like "dst host 192.168.1.11") which specifies the 
kind of packets we need to capture like specifing ip address or specific port and specifying who has this ip or port the dest
or the source*/
void define_filter(const char * expr)
{
    int32_t res = pcap_compile(handler,&fp,expr,1,interface_mask);
    if (res == -1)
    {
        printf("Error in defining filter\n");
    }
    res = pcap_setfilter(handler ,&fp);
    if (res == -1)
    {
        printf("Error in setting filter\n");
    }
    
}




/*this function is needed by read _packets as read_packet keeps reading frames in a loop 
without returning a packet so it need a function to process them while looping so in brief it the function
responsible for processing each packet*/
void callback_func(u_char* userarg, const struct pcap_pkthdr* pkthdr, const u_char*packet)
{

    printf("-----------------------------------------------------------------------\n");
    static uint32_t count =0;
    if (count == 0)
    {
        time1_sec = pkthdr->ts.tv_sec; 
        time1_usec = pkthdr->ts.tv_usec; 
    }
    else 
    {
        time2_sec = pkthdr->ts.tv_sec; 
        time2_usec = pkthdr->ts.tv_usec; 
    }

    printf("Packet no. %u\n",count);
    printf("Recieved at %li\n", pkthdr->ts.tv_sec);
    printf("Recieved at microsecond: %li\n", pkthdr->ts.tv_usec);
    printf("Lengh of information captured: %u\n",pkthdr->caplen);
    printf("Lengh of total packet: %u\n",pkthdr->len);
    //capture ethernet header
    struct ether_header eth_header;
    eth_header.ether_dhost[0] = *(packet++); 
    eth_header.ether_dhost[1] = *(packet++);
    eth_header.ether_dhost[2] = *(packet++);
    eth_header.ether_dhost[3] = *(packet++);
    eth_header.ether_dhost[4] = *(packet++);
    eth_header.ether_dhost[5] = *(packet++); 

    eth_header.ether_shost[0] = *(packet++);
    eth_header.ether_shost[1] = *(packet++);    
    eth_header.ether_shost[2] = *(packet++);   
    eth_header.ether_shost[3] = *(packet++);    
    eth_header.ether_shost[4] = *(packet++);      
    eth_header.ether_shost[5] = *(packet++);  

    eth_header.ether_type = ntohs(*((u_int16_t*)packet));
    uint64_t dest_mac_address =0;
    uint64_t source_mac_address = 0;
    for (int i =0 ;i <6 ;i++)
    {              
    dest_mac_address|=  (uint64_t)(eth_header.ether_dhost[i]) <<(MAC_ADDRESS_SIZE-(i+1)*BYTE_SIZE);
    source_mac_address|=(uint64_t) eth_header.ether_shost[i] << (MAC_ADDRESS_SIZE-(i+1)*BYTE_SIZE);

    }
    printf("Dest mac address:%lX\n",dest_mac_address);
    printf("Sender mac address:%lX\n",source_mac_address);
    printf("Ether type: %X\n", eth_header.ether_type);
    packet+=sizeof(eth_header.ether_type);
     // capture ip header 
     struct iphdr * ip = (struct iphdr *)packet;
     printf("Ip version:%u\n",ip->version);
     struct in_addr addr;
     addr.s_addr = ip->daddr;
     char *ip_address = inet_ntoa(addr);
     printf("Destination ip address is :%s\n",ip_address);
     addr.s_addr = ip->saddr;
     ip_address = inet_ntoa(addr);
     printf("Source ip address is :%s\n",ip_address);
     packet+=sizeof(struct iphdr);
     //capture tcp or udp header
     if (ip->protocol == 17)
     {
         printf("UDP packet\n");
        struct udphdr *uhdr = (struct udphdr *)packet;
        printf("Destination port is :%u\n",ntohs(uhdr->dest));
        printf("Destination port is :%u\n",ntohs(uhdr->source));
        packet+=sizeof(struct udphdr);

     }
      else if (ip->protocol == 6)
      {
        printf("TCP packet\n");
        struct tcphdr *thdr = (struct tcphdr *)packet;
        printf("Destination port is :%u\n",ntohs(thdr->dest));
        printf("Destination port is :%u\n",ntohs(thdr->source));
        printf("Sequence number is :%u\n",ntohs(thdr->seq));
        printf("window is :%u\n",ntohs(thdr->window));
        packet+=sizeof(struct tcphdr);


      }

    count++;
    printf("-----------------------------------------------------------------------\n");
}


long get_time_recieve(void){
    printf("%lld\n", time1_sec); 
    printf("%lld\n", time1_usec); 
    printf("%lld\n", time2_sec); 
    printf("%lld\n", time2_usec); 
    printf("diff in sec = %lld\n", time2_sec - time1_sec); 
    printf("diff in u_sec = %lld\n", time2_usec - time1_usec); 
    return 0; 
}

/*This function read packets according to filter ,if no filter ,all kind of packets will be captured ,it calls
the libpcap function pcap_loop which keeps reading packets and apply the callback fucntion to each of them until
num of packets specified is reached or pcap_break loop is executed
if num of packets is -1 read_packets will run infinitly ,we can stop it by calling function pcap_break loop
*/
void read_packets(int num_of_packets)
{
    uint8_t * args = NULL;
    int32_t res =pcap_loop(handler, num_of_packets ,callback_func,args);
}
void stop_receive()
{
    pcap_breakloop(handler);

}
void destroy_session(void)
{
    pcap_close(handler);

}
