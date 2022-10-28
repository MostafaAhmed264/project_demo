#include <pcap.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 2048   // maximum size of a packet to be captured
#define TURN_OFF_PROMISCUOUS_MODE 0 // means that only frames destined to our network card are captured 
#define TURN_ON_PROMISCUOUS_MODE 1  // means that any frames destined or not destined to our network card are captured 
#define WAIT_UNTIL_COPIED_MS  10 
  /*time in ms to wait until kernel take frames from the kernel space to the user space typical values
                                  are  0 , 10 , 512 ,1000  */
#define MAC_ADDRESS_SIZE 48
#define BYTE_SIZE 8
void libpcap_init(void);
void define_filter(const char * expr);
void callback_func(u_char* userarg, const struct pcap_pkthdr* pkthdr, const u_char*packet);
void read_packets(int num_of_packets);
void stop_receive();
void destroy_session(void);