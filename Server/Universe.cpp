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
	int iResult; //Input/output packet length
	ServerClientSocket** clients; //Connection sockets to the clients
	int clientsCount; //The size of 'clients'
	SOCKET tmp; //Socket for accepting clients. Used to initialize the element of 'clients'
	int ci;

	continueFlag = true;
	clientsCount = 0;
	clients = NULL;

	game = new Game("testgame", Server);
	printf("Game %s initialized\n", game->name);
	serverSocket = new ServerSocket("3127");
	//ci = Free;
	while (continueFlag)
	{
		//Accepting connections from clients
		tmp = accept(serverSocket->connectSocket, NULL, NULL);
		if (tmp != INVALID_SOCKET)
		{//Client connected
			clientsCount++;
			clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
			clients[clientsCount - 1] = new ServerClientSocket(tmp);
			printf("Client %d: Connected\n", clientsCount - 1);
		}

		//Receiving packets from connected clients
		for (ci = 0; ci < clientsCount; ci++)
		{
			iResult = clients[ci]->Receive(inPacket);
			if (iResult)
			{
				if (iResult > 0)
				{//Packet received
					printf("Packet received\n");
					switch (GetPacketType(inPacket))
					{
						case LogIn:
						{
							bool isOnline;
							int i, j;
							char query[256];
							std::vector<SqliteResult> sqliteResults;

							printf("Client %d trying to log in:\nLogin: %s\nPassword: %s\n", ci, inPacket + 3, inPacket + 3 + strlen(inPacket + 3) + 1);
							
							if (clients[ci]->character)
							{
								printf("Client is already logged in\n");
								break;
							}

							isOnline = false;
							for (i = 0; i < game->data->locationsCount; i++)
								for (j = 0; j < game->data->locations[i]->currentCharactersCount; j++) //TODO: GetCurrentMapObject. If NULL => Offline
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
							
							sprintf(query, "SELECT * FROM CurrentCharacter WHERE login='%s';", inPacket + 3);
							sqliteResults = SqliteGetRows(game->db, query);
							if (sqliteResults.size() == 0)
							{
								printf("Character does not exist\n");
								break;
							}
							else
							{
								if (strcmp(inPacket + 3 + strlen(inPacket + 3) + 1, sqliteResults[0].strings["password"].c_str()))
								{
									printf("Password does not match this account\n");
									break;
								}
								Location* location;
								CurrentCharacter* newCurrentCharacter;

								location = game->data->GetLocation(sqliteResults[0].integers["locationId"]);
								newCurrentCharacter = new CurrentCharacter(sqliteResults[0], location);
								location->AddCurrentCharacter(newCurrentCharacter);
								clients[ci]->character = newCurrentCharacter;
								printf("Character %s logged in\n", inPacket + 3);
								SetPacketLength(outPacket, 1);
								SetPacketType(outPacket, LoggedIn);
								PacketAddString(outPacket, game->name);
								PacketAddInt(outPacket, location->id);
								clients[ci]->Send(outPacket);
							}
							break;
						}
						case LogOut:
							break;
						case Say:
							switch(PacketGetByte(inPacket, 1))
							{
								case Public:
									printf("Message: %s\n",PacketGetString(inPacket,2));
									for (int i = 0; i < clientsCount; i++)
									{
										if (i != ci) clients[i]->Send(inPacket);
									}
									break;
								case Private:
									for (int i = 0; i < clientsCount; i++)
									{
										if (i != ci && clients[i]->character->id == PacketGetInt(inPacket, 2)) clients[i]->Send(inPacket);
									}
									break;
							}
							break;
						case Move:
							char movingStarted[256];

							printf("Client %d requested moving into %d %d\n", ci,PacketGetInt(inPacket, 1),PacketGetInt(inPacket, 5));

							SetPacketLength(movingStarted,1);
							SetPacketType(movingStarted,CharacterMoving);
							PacketAddInt(movingStarted,clients[ci]->character->id);
							PacketAddInt(movingStarted, PacketGetInt(inPacket, 1));
							PacketAddInt(movingStarted, PacketGetInt(inPacket, 5));
							for (int i = 0; i < clientsCount; i++)
							{
								if (i != ci) clients[i]->Send(movingStarted);
							}
							break;
					}
				}
				else if (iResult == -1)
				{//Client disconnected
					//TODO: data->UnspawnCharacter(clients[ci]->character)
					delete clients[ci]->character;

					delete clients[ci];
					clientsCount--;
					
					//Moving the last client to disconnected client position
					clients[ci] = clients[clientsCount];
					clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
					
					printf("Client %d: Disconnected\n", ci);
				}
				else
				{//Wrong packet from the server
					printf("Warning! Wrong packet from client %d\n", ci);
				}
			}

			//CreateItemSpawnedPacket(outPacket, Ground, 3, 5, 3, 4);
			//clients[0]->Send(outPacket);
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
		for (ci = 0; ci < clientsCount; ci++)
		{
			//outPacket[1] = '\0';
			strcpy(outPacket + 2, "test packet");
			SetPacketLength(outPacket, strlen(outPacket + 2) + 1);
			//clients[cClient]->Send(outPacket);
		}
		Sleep(200);
	}
	
	delete serverSocket;
	delete game;

	system("pause");
}
