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
	int iResult;

	iResult = recv(connectSocket, packet, 2, 0);
	if (iResult < 0)
	{
		iResult = WSAGetLastError();
		if (iResult != WSAEWOULDBLOCK && iResult != 0)
		{
			printf("Socket error: %d\n", iResult);
			return -1;
		}
		return 0;
	}
	if (iResult < 2)
	{
		return -2;
	}

	if (*((short int*)packet) > 254 || *((short int*)packet) < 1)
		return -3;

	iResult = recv(connectSocket, packet + 2, *((short int*)packet), 0);
	if (iResult < 0)
	{
		iResult = WSAGetLastError();
		if (iResult != WSAEWOULDBLOCK && iResult != 0)
		{
			printf("Socket error: %d\n", iResult);
			return -1;
		}
		return 0;
	}
	if (iResult != *((short int*)packet))
	{
		return -4;
	}

	return iResult;
}

bool ConnectSocket::Send(char *packet)
{
	return send(connectSocket, packet, *((short int*)packet) + 2, 0) == SOCKET_ERROR;
}
