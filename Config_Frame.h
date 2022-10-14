#ifndef CONFIG_FRAME_H
#define CONFIG_FRAME_H
/*tranport layer configuration values*/
typedef enum{
    UDP,TCP
}TransportLayerProtocol;
/*network layer configuration values*/
typedef enum{
    IPv4,IPv6
}NetworkLayerProtocol;
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
#endif