#pragma once

class ServerClientSocket :
	public ConnectSocket
{/*
	Holds the connection socket between server and client
*/
public:
	CurrentCharacter* character; //Pointer to a character used by current client

	ServerClientSocket(SOCKET& _connectSocket); /*
												Initializes with the accepted (connected) client socket
												_connectSocket: accepted socket
												*/
	~ServerClientSocket(void); //Disconnects the current client
};
