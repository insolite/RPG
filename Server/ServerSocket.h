#pragma once
#include "../Include/RPGator/ConnectSocket.h"

class ServerSocket :
	public ConnectSocket
{
public:
	ServerSocket(char* port);
	~ServerSocket(void);
};
