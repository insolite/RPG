#include "StdAfx.h"
#include "ServerSocket.h"

//Source code from http://msdn.microsoft.com/en-us/library/windows/desktop/ms737593(v=vs.85).aspx

ServerSocket::ServerSocket(char* port)
{
	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	u_long iMode = 1;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, port, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Create a SOCKET for connecting to server
	connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (connectSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket
	iResult = bind(connectSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(connectSocket);
		WSACleanup();
		return;
	}

	freeaddrinfo(result);

	iResult = listen(connectSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return;
	}

	//Setting socket as non-blocking
	ioctlsocket(connectSocket, FIONBIO, &iMode);

	printf("Server started on %s port\n\n", port);
}

ServerSocket::~ServerSocket(void)
{
	closesocket(connectSocket);
	WSACleanup();
}
