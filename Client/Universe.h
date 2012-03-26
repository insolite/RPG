#pragma once
#include "ClientSocket.h"

class Universe
{/*
 Main wrapper. Holds connection socket, game instance, etc.
 */
public:
	static Universe* instance; //Self instance
	ClientSocket* connectSocket; //Connection socket to the server
	Game* game; //Current game, that server is running
	CurrentCharacter* currentCharacter; //Current character, attached to the current client
	Location* currentLocation; //Current location of the current character

	void Run(); //Main loop

	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
};
