#include "StdAfx.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	instance = this;
}

Universe::~Universe(void)
{
	instance = NULL;
}

void Universe::Run()
{
	bool continueFlag; //Continue game or not
	char inPacket[256]; //Holds the input packet
	char outPacket[256]; //Holds the output packet
	int iResult; //The result of 'Receive' and 'Send'
	int ping; //TEST

	continueFlag = true;

	connectSocket = new ClientSocket("127.0.0.1", "3127");
	printf("Connected to the server\n");
	//TODO: receive game name
	//game = new Game();

	ping = SDL_GetTicks();
	
	while (continueFlag)
	{
		//Receving packet from the server
		iResult = connectSocket->Receive(inPacket);
		if (iResult)
		{
			if (iResult > 0)
			{//Packet received
				printf("Packet received: '%s'; Length: %d; Ping: %d;\n", inPacket + 2, GetPacketLength(inPacket), SDL_GetTicks() - ping);
				ping = SDL_GetTicks();
			}
			else if (iResult == -1)
			{//Disconnected from the server
				printf("Disconnected from the server\n");
				continueFlag = false;
			}
			else
			{//Wrong packet from the client
				printf("Warning! Wrong packet from server. Error code: %d\n", iResult);
				//continueFlag = false;
			}
		}

		//Drawing, events, etc.
		//TODO: correct disconnect in events
		SetPacketLength(outPacket, 1);
		SetPacketType(outPacket, LogIn);
		PacketAddString(outPacket, "admin");
		PacketAddString(outPacket, "1234");
		connectSocket->Send(outPacket);
		system("pause");
	}

	delete connectSocket;
	//delete game;

	system("pause"); //TEST
}
