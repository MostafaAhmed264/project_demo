#include <iostream>
#include <string>
using std::string;
#include "Config_Frame.h"
#include "construct_frame.h"

int main(void)
{
    int counter = 0;
    libnet_t* context_ptr1 = NULL;
    libnet_t* context_ptr2 = NULL;
    std::cout<<"hello" <<std::endl;
    Config_Frame c1(1400,UDP,IPv4);
    Config_Frame c2(1450,UDP,IPv4); 
    std::cout<<"configured frame"<<std::endl;

    c1.Dest_ip_address = "192.168.1.9";
    c1.Dest_Mac_Address =(const uint8_t*)"96:E2:3C:E7:0F:DB";
    c1.dest_port = 777; 

    c2.Dest_ip_address = "192.168.1.9";
    c2.Dest_Mac_Address =(const uint8_t*)"96:E2:3C:E7:0F:DB";
    c2.dest_port = 777; 

    std::cout<<"libnet initalized"<<std::endl;
    construct_frame(&c1,&context_ptr1);
    construct_frame(&c2,&context_ptr2);

    int flag = 0; 
    while(1)
    {
        if (flag == 0)
        {
            std::cout<<"constructed frame"<<std::endl;
            send_frame(&context_ptr1);
            flag = 1; 
        }
        else 
        {
            std::cout<<"constructed frame"<<std::endl;
            send_frame(&context_ptr2);
            flag = 0; 
        }
        counter++; 
    }
         
return 0;

}