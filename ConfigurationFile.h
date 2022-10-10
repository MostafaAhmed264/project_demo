#pragma once
#include <string>
typedef enum {
	TCP,
	UDP
}TransLayerProt_type;


typedef struct {
	std::string mac_Adress;
	std::string IP_Adress;
}Destination;

typedef struct {
	int			frameSize;
	TransLayerProt_type transnportLayerProtocol;
	int			time;
	Destination destination;
}Configuration;