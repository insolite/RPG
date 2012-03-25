#pragma once
#include "../Include/RPGator/ConnectSocket.h"

class ClientSocket :
	public ConnectSocket
{/*
	Holds the connection socket between client and server
*/
public:
	ClientSocket(char *serv, char *port); //Connects to the server 'serv:port'
	~ClientSocket(void); //Disconnects from the server
};
