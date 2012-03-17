#pragma once
#include "../Include/RPGator/ConnectSocket.h"

class ServerClientSocket :
	public ConnectSocket
{
public:
	ServerClientSocket(SOCKET& _connectSocket);
	~ServerClientSocket(void);
};
