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
	char inPacket[256], outPacket[256];
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
			printf("Packet received: '%s'; Length: %d; Ping: %d;\n", inPacket + 2, GetPacketLength(inPacket), SDL_GetTicks() - ping);
			ping = SDL_GetTicks();
		}
		else if (packetLength < -1)
		{
			printf("Warning! Wrong packet from server. Error code: %d\n", packetLength);
			//continueFlag = false;
		}

		//Drawing, events, etc.
		//TODO: correct disconnect in events
		SetPacketLength(outPacket, 1);
		SetPacketType(outPacket, 0);
		PacketAddString(outPacket, "admin");
		PacketAddString(outPacket, "MegaPassword");
		printf("sl: %d\n", GetPacketLength(outPacket));
		connectSocket->Send(outPacket);
		system("pause");
	}

	delete connectSocket;
	//delete game;

	system("pause");//TEST
}
