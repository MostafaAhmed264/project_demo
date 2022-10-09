#include <iostream>
#include "Config_Frame.h"
using namespace std;
#define Test_cases 0
class Config_Frame{
    private:
        int size_Of_Frame;
        TransportLayerProtocol enum_transport_layer_protocol;
        NetworkLayerProtocol enum_network_layer_protocol;
    public:
    /*default values size of frame =64 , transport protocol is UDP, Network protocol is IPv4*/
    Config_Frame(){
        size_Of_Frame=64;
        enum_transport_layer_protocol=UDP;
        enum_network_layer_protocol=IPv4;
    }
    Config_Frame(int size,TransportLayerProtocol enum_transport_layer_protocol,NetworkLayerProtocol enum_network_layer_protocol){
        this->size_Of_Frame=size;
        this->enum_transport_layer_protocol=enum_transport_layer_protocol;
        this->enum_network_layer_protocol=enum_network_layer_protocol;
    }
    int getSizeOfFrame(void){return this->size_Of_Frame;}
    TransportLayerProtocol getProtocolOfTransportLayer(void){return this->enum_transport_layer_protocol;}
    NetworkLayerProtocol getProtocolOfNetworkLayer(void){return this->enum_network_layer_protocol;}
    void setSizeOfFrame(int size){this->size_Of_Frame=size;}
    void setProtocolOfTransportLayer(TransportLayerProtocol enum_transport_layer_protocol){
        this->enum_transport_layer_protocol=enum_transport_layer_protocol;}
    void setProtocolOfNetworkLayer(NetworkLayerProtocol enum_network_layer_protocol){
        this->enum_network_layer_protocol= enum_network_layer_protocol;
    }
};
#if(Test_case ==1)
int main(){
    Config_Frame c;
    printf("%d %d %d\n",c.getSizeOfFrame(),c.getProtocolOfNetworkLayer(),c.getProtocolOfTransportLayer());
    Config_Frame c1(100,TCP,IPv4);
    printf("%d %d %d\n",c1.getSizeOfFrame(),c1.getProtocolOfNetworkLayer(),c1.getProtocolOfTransportLayer());
    c1.setSizeOfFrame(1050);
    c1.setProtocolOfNetworkLayer(IPv6);
    c1.setProtocolOfTransportLayer(UDP);
    printf("%d %d %d",c1.getSizeOfFrame(),c1.getProtocolOfNetworkLayer(),c1.getProtocolOfTransportLayer());
    return 0;
}
#endif