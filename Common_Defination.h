#pragma once
typedef enum {
	TCP,
	UDP
}TransportLayerProtocol_type;

typedef enum {
	IPv4, IPv6
}NetworkLayerProtocol;

typedef enum {
	IDLE,
	ACTIVE
}State;