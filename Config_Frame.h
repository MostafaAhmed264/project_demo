#ifndef CONFIG_FRAME_H
#define CONFIG_FRAME_H
#include <string>
using std::string;
/*tranport layer configuration values*/
typedef enum{
    UDP,TCP
}TransportLayerProtocol;
/*network layer configuration values*/
typedef enum{
    IPv4,IPv6
}NetworkLayerProtocol;
class Config_Frame{
    private:
        int size_Of_Frame;
        TransportLayerProtocol enum_transport_layer_protocol;
        NetworkLayerProtocol   enum_network_layer_protocol;
        
    public:
    const uint8_t* Dest_Mac_Address;
    char* Dest_ip_address; 
    int dest_port; 
    Config_Frame();
    Config_Frame(int size,TransportLayerProtocol enum_transport_layer_protocol,NetworkLayerProtocol enum_network_layer_protocol);
    /*return used size of frame*/
    int getSizeOfFrame(void); 
    /*return used transport layer protocal in frame*/
    TransportLayerProtocol getProtocolOfTransportLayer(void);
    /*return used network layer protocal in frame*/
    NetworkLayerProtocol getProtocolOfNetworkLayer(void);
    /*change size of frame*/
    void setSizeOfFrame(int size);
    /*change used transport layer protocal in frame*/
    void setProtocolOfTransportLayer(TransportLayerProtocol enum_transport_layer_protocol);
    /*change used network layer protocal in frame*/
    void setProtocolOfNetworkLayer(NetworkLayerProtocol enum_network_layer_protocol);
    
};
#endif