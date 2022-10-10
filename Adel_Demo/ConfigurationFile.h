#ifndef	  CONFIGURATIONFILE_
#define   CONFIGURATIONFILE_
#include <string>
#include "Common_Defination.h"


typedef struct {
	std::string mac_Adress;
	std::string IP_Adress;
}Destination;

typedef enum {
	START , 
	END 
}Command_type;

typedef struct {
	Command_type						commandB3bos		        ;
	int							frameSize               ;
	TransportLayerProtocol_type 				transnportLayerProtocol ;
	int							time		        ;
	Destination						destination             ;
}Configuration;

#endif
