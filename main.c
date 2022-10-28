#include "receive_frame.h"
int main(void)
{
    long time; 
    libpcap_init();
    //optional filter
    define_filter("dst port 777");
    read_packets(10000);
    time = get_time_recieve(); 
    printf("%ld\n", time); 
    destroy_session();

}