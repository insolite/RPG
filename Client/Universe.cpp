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
	SetPacketLength(outPacket, 1);
	SetPacketType(outPacket, LogIn);
	PacketAddString(outPacket, "admin");
	PacketAddString(outPacket, "1234");
	connectSocket->Send(outPacket);

	ping = SDL_GetTicks(); //TEST

	currentCharacter = NULL;
	
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
				switch (GetPacketType(inPacket))
				{
					case LoggedIn:
						game = new Game(inPacket + 3, Client);
						printf("Game %s initialized\n", game->name);
						currentLocation = game->data->GetLocation(atoi(inPacket + 3 + strlen(inPacket + 3) + 1));
						break;
					case CharacterSpawned:
						if (!currentCharacter)
						{
							currentCharacter = new CurrentCharacter(inPacket);
							currentLocation->AddCurrentCharacter(currentCharacter);
						}
						else
						{
							currentLocation->AddCurrentCharacter(new CurrentCharacter(inPacket));
						}
						break;
					case Say:
						printf("Message: %s\n", PacketGetString(inPacket, 6));
						break;
					case CharacterMoving:
						printf("Character #%d is moving to %d %d\n",PacketGetInt(inPacket,1),PacketGetInt(inPacket,5),PacketGetInt(inPacket,9));
						break;
					case ItemSpawned:
						printf ("Type: %d\n", (PacketGetByte(inPacket, 1)));
						switch(PacketGetByte(inPacket, 1))
						{
							case Ground:
								//Adding item to currentItems of the location
								break;
								
						}
				}
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

		Sleep(200);
	}

	delete connectSocket;
	delete game;

	system("pause"); //TEST
}
