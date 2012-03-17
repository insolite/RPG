#include "StdAfx.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	instance = this;
}

Universe::~Universe(void)
{
}

void Universe::Run()
{
	bool continueFlag;
	char inPacket[256];
	int packetLength;
	int ping;

	continueFlag = true;

	connectSocket = new ClientSocket("127.0.0.1", "3127");
	printf("Connected to the server\n");
	//TODO: receive game name
	//game = new Game();

	ping = SDL_GetTicks();

	while (continueFlag)
	{
		packetLength = connectSocket->Receive(inPacket);
		if (packetLength > 0)
		{
			//printf("Packet received: %s; Ping: %d\n", inPacket, SDL_GetTicks() - ping);
			ping = SDL_GetTicks();
		}
		else
		{
			printf("Disconnected from the server: Server shutdown\n");
			continueFlag = false;
		}

		//Drawing, events, etc.
		//TODO: correct disconnect in events
	}

	delete connectSocket;
	//delete game;

	system("pause");//TEST
}
