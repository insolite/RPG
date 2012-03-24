#pragma once
#include "ServerSocket.h"
#include "ServerClientSocket.h"

class Universe
{/*
 Main wrapper. Holds connection socket, game instance, etc.
 */
public:
	static Universe* instance; //Self instance
	ServerSocket* serverSocket; //Server connection socket
	Game* game; //Game instance

	void Run(); //Main loop
	
	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
};

