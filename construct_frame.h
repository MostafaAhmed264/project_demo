#include "Config_Frame.h"
#include <libnet.h> 
#define SOURCE_PORT 9980
#define DEST_PORT 9985
#define ETHERNET_HEADER_SIZE 14
#define IPV4_HEADER_SIZE 20
#define IPV6_HEADER_SIZE 40
#define TCP_HEADER_SIZE 20
#define UDP_HEADER_SIZE 8
#define IPV4_PROTOCOL_FIELD_UDP 17
#define IPV4_PROTOCOL_FIELD_TCP 6
#define IPV4_ETHER_TYPE_VALUE 0x800
#define IPV6_ETHER_TYPE_VALUE 0x86DD
#define LINK_LAYER_PACKET LIBNET_LINK
#define NETWORK_LAYER_IPV4_PACKET LIBNET_RAW4 
#define NETWORK_LAYER_IPV6_PACKET LIBNET_RAW6
extern libnet_t * context_ptr;
extern uint64_t total_num_bytes_sent;
void initialize_libnet(int socket_type);
void construct_frame(Config_Frame* c_ptr);
void send_frame();
void destroy_libnet_context();


