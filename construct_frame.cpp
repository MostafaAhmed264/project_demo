#include <iostream>
#include "construct_frame.h"
#include "Config_Frame.h"
libnet_t* context_ptr = NULL;
uint64_t total_num_bytes_sent =0;
uint64_t num_frames_sent;
char errormsg[200];
void initialize_libnet(int socket_type )
{
    context_ptr = libnet_init(socket_type,NULL,errormsg);
    
}
void construct_frame(Config_Frame* c_ptr)
{
    /*add payload of any charachter (dummy frame)*/
    uint32_t payload_size = c_ptr->getSizeOfFrame() -(UDP_HEADER_SIZE+ ETHERNET_HEADER_SIZE +IPV4_HEADER_SIZE);
    uint8_t* ptr = (uint8_t*)malloc(sizeof(char)*payload_size);
    memset(ptr,'m',payload_size);
    libnet_ptag_t ptag_payload = libnet_build_data(ptr,payload_size,context_ptr,0);
     

    if (c_ptr->getProtocolOfTransportLayer() == UDP && c_ptr->getProtocolOfNetworkLayer()==IPv4)
    {
    /*build udp header*/
    libnet_ptag_t ptag_udp = libnet_build_udp(SOURCE_PORT,DEST_PORT,c_ptr->getSizeOfFrame()-(ETHERNET_HEADER_SIZE +IPV4_HEADER_SIZE),0 ,NULL,0,context_ptr,0);
    int len;
    /*convert ip string to integer value*/
    uint32_t dest_ip_address = libnet_name2addr4(context_ptr,c_ptr->Dest_ip_address,LIBNET_DONT_RESOLVE);
    /*build ipv4 header*/
    libnet_ptag_t ptag_ipv4 = libnet_autobuild_ipv4((c_ptr->getSizeOfFrame()-ETHERNET_HEADER_SIZE),IPV4_PROTOCOL_FIELD_UDP,dest_ip_address,context_ptr);
    /*convert mac address aa:bb:cc etc format into binary format */
    uint8_t* dest_mac_address =libnet_hex_aton((const char*)c_ptr->Dest_Mac_Address ,&len);
    /*build ethernet header*/
    libnet_ptag_t ptag_ether = libnet_autobuild_ethernet(dest_mac_address,IPV4_ETHER_TYPE_VALUE ,context_ptr);
    }
    else if (c_ptr->getProtocolOfTransportLayer() == UDP && c_ptr->getProtocolOfNetworkLayer()==IPv6)
    {
        libnet_ptag_t ptag_udp_2= libnet_build_udp(SOURCE_PORT,DEST_PORT,c_ptr->getSizeOfFrame()-(ETHERNET_HEADER_SIZE +IPV6_HEADER_SIZE),0 ,NULL,0,context_ptr,0);

        //libnet_ptag_t ptag_ipv6 = libnet_autobuild_ipv6((c_ptr->getSizeOfFrame()-ETHERNET_HEADER_SIZE),IPV4_PROTOCOL_FIELD_UDP,DESTINATION_IPV6_ADDRESS,t);
        libnet_ptag_t ptag_ether = libnet_autobuild_ethernet(c_ptr-> Dest_Mac_Address ,IPV6_ETHER_TYPE_VALUE ,context_ptr);


    }
    /*
    else if (c_ptr->getProtocolOfTransportLayer() == TCP && c_ptr->getProtocolOfNetworkLayer()==IPV4)
    {
        libnet_ptag_t ptag_tcp = libnet_build_udp(SORCE_PORT ,DEST_PORT,)






    }
      else if (c_ptr->getProtocolOfTransportLayer() == TCP && c_ptr->getProtocolOfNetworkLayer()==IPV6)
    {
        



    }
    */
}
void send_frame()
{
    uint32_t num_bytes_sent = libnet_write(context_ptr);
    total_num_bytes_sent+=num_bytes_sent;
    std::cout<<"frame number:" <<num_frames_sent<<"     bytes sent:" <<num_bytes_sent;
    num_frames_sent++;
}
void destroy_libnet_context()
{
    libnet_destroy(context_ptr);
}