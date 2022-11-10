#include <iostream>
#include <string>
#include <omp.h>
using namespace std;
using std::string;
#include "Config_Frame.h"
#include "construct_frame.h"
#include <thread>
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
    c1.Dest_Mac_Address =(const uint8_t*)"3C:2C:30:9B:3B:90";
    c1.dest_port = 777; 

    c2.Dest_ip_address = "192.168.1.9";
    c2.Dest_Mac_Address =(const uint8_t*)"3C:2C:30:9B:3B:90";
    c2.dest_port = 777; 

    std::cout<<"libnet initalized"<<std::endl;
    
    construct_frame(&c1,&context_ptr1);
    construct_frame(&c2,&context_ptr2);

    int flag = 0; 
    while(counter < 20000)
    {
        if (flag == 0)
        {
            modifiy_payload(&context_ptr1, &c1); 
            //std::cout<<"constructed frame"<<std::endl;
            send_frame(&context_ptr1);
            flag = 1; 
        }
        else 
        {
            modifiy_payload(&context_ptr2, &c2);
            //std::cout<<"constructed frame"<<std::endl;
            send_frame(&context_ptr2);
            flag = 0; 
        }
        counter++; 
    }
         
return 0;

}