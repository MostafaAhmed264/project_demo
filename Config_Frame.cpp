#include <iostream>
#include "Config_Frame.h"
using namespace std;
    /*default values size of frame =64 , transport protocol is UDP, Network protocol is IPv4*/
    Config_Frame::Config_Frame(){
        size_Of_Frame=64;
        enum_transport_layer_protocol=UDP;
        enum_network_layer_protocol=IPv4;
    }
    Config_Frame::Config_Frame(int size,TransportLayerProtocol enum_transport_layer_protocol,NetworkLayerProtocol enum_network_layer_protocol){
        this->size_Of_Frame=size;
        this->enum_transport_layer_protocol=enum_transport_layer_protocol;
        this->enum_network_layer_protocol=enum_network_layer_protocol;
    }
    int Config_Frame::getSizeOfFrame(void){return this->size_Of_Frame;}
    TransportLayerProtocol Config_Frame::getProtocolOfTransportLayer(void){return this->enum_transport_layer_protocol;}
    NetworkLayerProtocol  Config_Frame::getProtocolOfNetworkLayer(void){return this->enum_network_layer_protocol;}
    void Config_Frame::setSizeOfFrame(int size){this->size_Of_Frame=size;}
    void Config_Frame::setProtocolOfTransportLayer(TransportLayerProtocol enum_transport_layer_protocol){
        this->enum_transport_layer_protocol=enum_transport_layer_protocol;}
    void Config_Frame::setProtocolOfNetworkLayer(NetworkLayerProtocol enum_network_layer_protocol){
        this->enum_network_layer_protocol= enum_network_layer_protocol;
    }
    unsigned int Config_Frame::getIPAdress(void){
        return this->IP_address;
    }
    /*set IP Address*/
    void Config_Frame::setIPAdress(unsigned int IP_address){
        this->IP_address=IP_address;
    }
     /*return MAC Address*/
    char * Config_Frame::getMACAdress(){
        return this->Mac_address;
    }
    /*set MAC Address*/
    void Config_Frame::setMACAdress(char* Mac_address){
    this->Mac_address=Mac_address;
    }