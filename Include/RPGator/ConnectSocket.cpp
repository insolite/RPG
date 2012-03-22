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
	int length;

	length = recv(connectSocket, packet, 2, 0);
	if (length < 2)
	{
		return -1;
	}

	if (*((short int*)packet) > 254)
		return -2;

	length = recv(connectSocket, packet + 2, *((short int*)packet), 0);
	if (length != *((short int*)packet))
	{
		printf("l: %d pl: %d\n", length, *((short int*)packet));
		return -3;
	}

	return length;
}

bool ConnectSocket::Send(char *packet)
{
	return send(connectSocket, packet, *((short int*)packet) + 2, 0) == SOCKET_ERROR;
}
