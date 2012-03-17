#pragma once
#include "ClientSocket.h"

class Universe
{
public:
	static Universe* instance;
	ClientSocket* connectSocket;
	//Game game;

	int ConnectServer();
	void Run();

	Universe(void);
	~Universe(void);
};
