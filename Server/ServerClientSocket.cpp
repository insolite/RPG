#include "StdAfx.h"
#include "ServerClientSocket.h"

//Source code from http://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx

ServerClientSocket::ServerClientSocket(SOCKET& _connectSocket)
{
	connectSocket = _connectSocket;
}

ServerClientSocket::~ServerClientSocket(void)
{
	int iResult;

	iResult = shutdown(connectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return;
	}

	closesocket(connectSocket);
}
