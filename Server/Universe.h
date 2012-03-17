#pragma once
#include "ServerSocket.h"
#include "ServerClientSocket.h"

class Universe
{
public:
	static Universe* instance;
	ServerClientSocket** clients;
	int clientsCount;

	ServerSocket* serverSocket;
	Game* game;

	void Run();
	
	Universe(void);
	~Universe(void);
};

