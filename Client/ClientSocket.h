#pragma once
#include "../Include/RPGator/ConnectSocket.h"

class ClientSocket :
	public ConnectSocket
{
public:
	ClientSocket(char *serv, char *port);
	~ClientSocket(void);
};
