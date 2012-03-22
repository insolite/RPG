#include "StdAfx.h"
#include "Universe.h"

Universe* Universe::instance;

enum Packet
{
	LogIn = 0,

};

Universe::Universe(void)
{
	instance = this;
	clientsCount = 0;
	clients = NULL;
}

Universe::~Universe(void)
{
}

void Universe::Run()
{
	bool continueFlag;
	SOCKET tmp;
	int cClient;
	char inPacket[256], outPacket[256];
	int packetLength;
	int iResult;

	continueFlag = true;

	game = new Game("testgame");
	/*
	if (!Game::instance)
	{
		system("pause");
		return;
	}
	*/
	printf("Game %s initialized\n", game->name);
	serverSocket = new ServerSocket("3127");
	
	while (continueFlag)
	{
		//Users login
		tmp = accept(serverSocket->connectSocket, NULL, NULL);
		if (tmp != INVALID_SOCKET)
		{
			clientsCount++;
			clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
			clients[clientsCount - 1] = new ServerClientSocket(tmp);
			printf("Client %d: Connected\n", clientsCount - 1);
		}

		//Receive packets
		for (cClient = 0; cClient < clientsCount; cClient++)
		{
			packetLength = clients[cClient]->Receive(inPacket);
			if (packetLength > 0)
			{
				printf("Packet received\n");
				switch (inPacket[2])
				{
					case LogIn:
						printf("Client %d trying to log in:\nLogin: %s\nPassword: %s\n", cClient, inPacket + 3, inPacket + 3 + strlen(inPacket + 3) + 1);
						
						int i, j, result;
						
						bool isOnline;

						isOnline = false;
						for (i = 0; i < game->data->locationsCount; i++)
							for (j = 0; j < game->data->locations[i]->currentCharactersCount; j++)
								if (!strcmp(game->data->locations[i]->currentCharacters[j]->login, inPacket + 3))
								{
									isOnline = true;
									i = game->data->locationsCount;
									break;
								}
						if (isOnline)
						{
							printf("Character is currently in use\n");
							break;
						}
						
						char query[256];
						std::map<std::string, std::string> strings;
						std::map<std::string, int> integers;

						sprintf(query, "SELECT * FROM CurrentCharacter WHERE login='%s';", inPacket + 3);
						result = SqliteGetRow(game->db, query, strings, integers);
						if (result < 0)
						{
							strings.clear();
							integers.clear();
							break;
						}
						else if (result == 0)
						{
							printf("Character does not exist\n");
							strings.clear();
							integers.clear();
							break;
						}
						else
						{
							/*
							if (integers["online"])
							{
								printf("Character is currently in use\n");
								strings.clear();
								integers.clear();
								break;
							}
							*/
							for (i = 0; i < game->data->locationsCount; i++)
								if (game->data->locations[i]->id == integers["locationId"])
								{
									CurrentCharacter* newCurrentCharacter = new CurrentCharacter(strings, integers);
									if (game->data->locations[i]->AddCurrentCharacter(newCurrentCharacter))
										delete newCurrentCharacter;
									break;
								}
						}
						strings.clear();
						integers.clear();
						break;
				}
			}
			else if (packetLength < -1)
			{
				printf("Warning! Wrong packet from client %d\n", cClient);
			}
			else
			{
				iResult = WSAGetLastError();
				if (iResult != WSAEWOULDBLOCK && iResult != 0)
				{
					delete clients[cClient];
					clientsCount--;
					
					/*
					//Shift
					for (j = i; j < clientsCount; j++)
						clients[j] = clients[j + 1];
					*/
					//Last client move
					clients[cClient] = clients[clientsCount];

					clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
					printf("Client %d: Socket error: %d\n", cClient, iResult);
					printf("Client %d: Disconnected\n", cClient);
					//continueFlag = false; //TEST
				}
			}
		}

		//Simulating world
		/*
		printf("\nCharacters online:\n");
		int i, j;
		for (i = 0; i < game->data->locationsCount; i++)
		{
			for (j = 0; j < game->data->locations[i]->currentCharactersCount; j++)
			{
				printf("\t%s\n", game->data->locations[i]->currentCharacters[j]->login);
			}
		}
		*/
		//TEST
		for (cClient = 0; cClient < clientsCount; cClient++)
		{
			//outPacket[1] = '\0';
			strcpy(outPacket + 2, "test packet");
			SetPacketLength(outPacket, strlen(outPacket + 2) + 1);
			clients[cClient]->Send(outPacket);
		}
		//Sleep(200);
	}
	
	delete serverSocket;
	delete game;

	system("pause");
}
