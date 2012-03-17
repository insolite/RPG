#include "StdAfx.h"
#include "ConnectSocket.h"

ConnectSocket::ConnectSocket(void)
{
}

ConnectSocket::~ConnectSocket(void)
{
}

int ConnectSocket::Receive(char *packet)
{
	return recv(connectSocket, packet, 256, 0);
}

bool ConnectSocket::Send(char *packet, int length)
{
	return send(connectSocket, packet, length, 0) == SOCKET_ERROR;
}
