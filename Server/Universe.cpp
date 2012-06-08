#include "StdAfx.h"
#include "LuaFunctions.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	instance = this;
	luaState = luaL_newstate();
	LuaFunctions::RegisterFunctions(luaState);
	log = fopen("server.log", "wt");
}

Universe::~Universe(void)
{
	instance = NULL;
	lua_close(luaState);
	fclose(log);
}

void Universe::Run(char* gameName)
{
	bool continueFlag; //Continue game or not
	char inPacket[256]; //Holds the input packet
	char outPacket[256]; //Holds the output packet
	int iResult; //Input/output packet length
	ServerClientSocket** clients; //Connection sockets to the clients
	int clientsCount; //The size of 'clients'
	SOCKET tmp; //Socket for accepting clients. Used to initialize the element of 'clients'
	int ci;

	int lastStepTime;
	int currentTime;

	lastStepTime = 0;
	continueFlag = true;
	clientsCount = 0;
	clients = NULL;

	game = new Game(gameName, Server);
	printf("Game %s initialized\n", game->name);
	serverSocket = new ServerSocket("3127");
	
	while (continueFlag)
	{
		//Accepting connections from clients
		tmp = accept(serverSocket->connectSocket, NULL, NULL);
		if (tmp != INVALID_SOCKET)
		{ //Client connected
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
								newCurrentCharacter->connectSocket = clients[ci];
								location->SpawnCharacter(newCurrentCharacter);
								clients[ci]->character = newCurrentCharacter;
								printf("Character %s logged in\n", newCurrentCharacter->login);
								CreatePacket(outPacket, LoggedIn, "%s%i", game->name, location->id);
								clients[ci]->Send(outPacket);
								CreatePacket(outPacket, CharacterSpawned, "%i%i%f%f%s",
									newCurrentCharacter->id,
									newCurrentCharacter->base->id,
									newCurrentCharacter->x,
									newCurrentCharacter->y,
									newCurrentCharacter->login
									);
								//Send to all that character spawned
								//For the newCurrentCharacter is will be the first CharacterSpawned packet (his character)
								for (int i = 0; i < newCurrentCharacter->currentLocation->currentCharactersCount; i++)
								{
									newCurrentCharacter->currentLocation->currentCharacters[i]->connectSocket->Send(outPacket);
								}

								//Send to one client that all spawned
								for (int i = 0; i < newCurrentCharacter->currentLocation->currentCharactersCount; i++)
								{
									if (newCurrentCharacter != newCurrentCharacter->currentLocation->currentCharacters[i])
									{ //Not current client. We did it in the previous loop
										CreatePacket(outPacket, CharacterSpawned, "%i%i%f%f%s",
											newCurrentCharacter->currentLocation->currentCharacters[i]->id,
											newCurrentCharacter->currentLocation->currentCharacters[i]->base->id,
											newCurrentCharacter->currentLocation->currentCharacters[i]->x,
											newCurrentCharacter->currentLocation->currentCharacters[i]->y,
											newCurrentCharacter->currentLocation->currentCharacters[i]->login
											);
										newCurrentCharacter->connectSocket->Send(outPacket);
									}
								}
								//NPC
								for (int i = 0; i < newCurrentCharacter->currentLocation->currentNPCsCount; i++)
								{
									CreatePacket(outPacket, NPCSpawned, "%i%i%f%f",
										newCurrentCharacter->currentLocation->currentNPCs[i]->id,
										newCurrentCharacter->currentLocation->currentNPCs[i]->base->id,
										newCurrentCharacter->currentLocation->currentNPCs[i]->x,
										newCurrentCharacter->currentLocation->currentNPCs[i]->y
										);
									newCurrentCharacter->connectSocket->Send(outPacket);
								}
								//Statics
								for (int i = 0; i < newCurrentCharacter->currentLocation->currentStaticsCount; i++)
								{
									CreatePacket(outPacket, StaticSpawned, "%i%i%f%f",
										newCurrentCharacter->currentLocation->currentStatics[i]->id,
										newCurrentCharacter->currentLocation->currentStatics[i]->base->id,
										newCurrentCharacter->currentLocation->currentStatics[i]->x,
										newCurrentCharacter->currentLocation->currentStatics[i]->y
										);
									newCurrentCharacter->connectSocket->Send(outPacket);
								}
								//Items
								for (int i = 0; i < newCurrentCharacter->currentLocation->currentItemsCount; i++)
								{
									CreatePacket(outPacket, ItemSpawned, "%i%i%f%f%b%i",
										newCurrentCharacter->currentLocation->currentItems[i]->id,
										newCurrentCharacter->currentLocation->currentItems[i]->base->id,
										newCurrentCharacter->currentLocation->currentItems[i]->x,
										newCurrentCharacter->currentLocation->currentItems[i]->y,
										Ground,
										newCurrentCharacter->currentLocation->currentItems[i]->count
										);
									newCurrentCharacter->connectSocket->Send(outPacket);
								}
								//Inventory
								for (int i = 0; i < newCurrentCharacter->currentItemsCount; i++)
								{
									CreatePacket(outPacket, ItemSpawned, "%i%i%f%f%b%i",
										newCurrentCharacter->currentItems[i]->id,
										newCurrentCharacter->currentItems[i]->base->id,
										0,
										0,
										Inventory,
										newCurrentCharacter->currentItems[i]->count
										);
									newCurrentCharacter->connectSocket->Send(outPacket);
								}
								//Skills
								for (int i = 0; i < newCurrentCharacter->currentSkillsCount; i++)
								{
									CreatePacket(outPacket, SkillSpawned, "%i%i",
										newCurrentCharacter->currentSkills[i]->id,
										newCurrentCharacter->currentSkills[i]->base->id
										);
									newCurrentCharacter->connectSocket->Send(outPacket);
								}
							}
							break;
						}
						case LogOut:
							break;
						case Register:
						{
							char* login;
							char* password;
							Character *character;
							if (character = game->resources->GetCharacter(PacketGetInt(inPacket, 1)))
							{
								char query[256];
								
								login = PacketGetString(inPacket, 5);
								password = PacketGetString(inPacket, 5 + strlen(login) + 1);

								sprintf(query, "SELECT * FROM CurrentCharacter WHERE login='%s';", login);
								if (SqliteGetRows(game->db, query).size() == 0)
								{
									//TODO: default location, coordinates
									//TODO: without UnSpawnCharacter
									//TODO: password check
									game->data->locations[0]->UnSpawnCharacter(game->data->locations[0]->AddCharacter(character, 16, 16, login, password));
									CreatePacket(outPacket, RegisterOK, "");
								}
								else
								{
									CreatePacket(outPacket, RegisterFail, "%b", AccountAlreadyExists);
								}
								clients[ci]->Send(outPacket);
							}
							break;
						}
						case Say:
							CreatePacket(outPacket, Say, "%b%i%s",
								PacketGetByte(inPacket, 1),
								clients[ci]->character->id,
								PacketGetString(inPacket, PacketGetByte(inPacket, 1) == Private ? 6 : 2)
								);
							switch (PacketGetByte(inPacket, 1))
							{
								case Public: //%b%i%s
									for (int i = 0; i < clientsCount; i++)
									{
										clients[i]->Send(outPacket);
									}
									break;
								case Private: //%b%i%i%s
									for (int i = 0; i < clientsCount; i++)
									{
										if (clients[i]->character->id == PacketGetInt(inPacket, 2))
										{
											clients[i]->Send(outPacket);
											break;
										}
									}
									break;
							}
							break;
						case Move:
						{
							f32 newX, newY;
							ScanPacket(inPacket, "%f%f", &newX, &newY);
							if (newX > 0 && newX < clients[ci]->character->currentLocation->width //TODO: x >= 0
							 && newY > 0 && newY < clients[ci]->character->currentLocation->height) //TODO: x >= 0
							{
								clients[ci]->character->movingX = newX;
								clients[ci]->character->movingY = newY;
								clients[ci]->character->RecalculateDelta();

								CreatePacket(outPacket, CharacterMoving, "%i%f%f", clients[ci]->character->id, newX, newY);
								for (int i = 0; i < clients[ci]->character->currentLocation->currentCharactersCount; i++)
								{
									clients[i]->Send(outPacket);
								}
							}
							break;
						}
						case SkillUse:
						{
							CurrentSkill* currentSkill = clients[ci]->character->GetSkill(PacketGetInt(inPacket, 1));
							int targetType;
							int targetMapObjectId;
							CurrentMapObject<MapObject>* targetMapObject;

							if (currentSkill)
							{
								if (((int)GetTickCount() - currentSkill->lastUse) > currentSkill->base->useDelay)
								{
									char str[512]; //For init script variables
								
									targetType = PacketGetByte(inPacket, 5);
									targetMapObjectId = PacketGetInt(inPacket, 6);
									switch (targetType)
									{
										case 0:
											targetMapObject = (CurrentMapObject<MapObject>*)clients[ci]->character->currentLocation->GetNPC(targetMapObjectId);
											break;
										case 3:
											targetMapObject = (CurrentMapObject<MapObject>*)clients[ci]->character->currentLocation->GetCharacter(targetMapObjectId);
											break;
										default:
											targetMapObject = NULL;
											targetType = -1;
											targetMapObjectId = 0;
											Log(Warning, "Client requested bad target type");
											break;
									}

									if (targetType == 3)
									{
										sprintf(str, "\
											CHARACTER_ID=%d;\
											CHARACTER_BID=%d;\
											CHARACTER_X=%.0f;\
											CHARACTER_Y=%.0f;\
											CHARACTER_LOCATION_ID=%d;\
											TARGET_TYPE=%d;\
											TARGET_ID=%d;\
											TARGET_X=%.0f;\
											TARGET_Y=%.0f;\
											",
											clients[ci]->character->id,
											clients[ci]->character->base->id,
											clients[ci]->character->x,
											clients[ci]->character->y,
											clients[ci]->character->currentLocation->id,
											targetType,
											targetMapObject ? targetMapObjectId : 0,
											targetMapObject ? ((CurrentCharacter*)targetMapObject)->x : -1,
											targetMapObject ? ((CurrentCharacter*)targetMapObject)->y : -1
											);
										luaL_dostring(luaState, str);
										luaL_dofile(luaState, currentSkill->base->scriptPath);
										currentSkill->lastUse = GetTickCount();
									}
								}
							}
							else
							{
								Log(Warning, "Client requested skill use which is not in the list of skills of his character");
							}
							break;
						}
						case ItemUse:
						{
							CurrentItem* currentItem = clients[ci]->character->GetItem(PacketGetInt(inPacket, 1));
							if (currentItem)
							{
								char str[512]; //For init script variables

								sprintf(str, "\
									CHARACTER_ID=%d;\
									CHARACTER_BID=%d;\
									CHARACTER_X=%d;\
									CHARACTER_Y=%d;\
									CHARACTER_LOCATION_ID=%d;\
									",
									clients[ci]->character->id,
									clients[ci]->character->base->id,
									clients[ci]->character->x,
									clients[ci]->character->y,
									clients[ci]->character->currentLocation->id
									);
								luaL_dostring(luaState, str);
								luaL_dofile(luaState, currentItem->base->path);
							}
							else
							{
								Log(Warning, "Client requested item use which is not in the list of items of his character");
							}
							break;
						}
						case DialogOpen:
						{
							CurrentNPC* currentNPC = clients[ci]->character->currentLocation->GetNPC(PacketGetInt(inPacket, 1));
							if (currentNPC)
							{
								f32 distance = vector2d<f32>(currentNPC->x, currentNPC->y).getDistanceFrom(vector2d<f32>(clients[ci]->character->x, clients[ci]->character->y));
								if (distance < 3.0f)
								{
									char str[512]; //For init script variables

									sprintf(str, "\
										EVENT_TYPE=%d;\
										EVENT_TYPE_ATTACK=0;\
										EVENT_TYPE_KILL=1;\
										EVENT_TYPE_DIALOG=2;\
										DIALOG_ID=%d;\
										NPC_ID=%d;\
										CHARACTER_ID=%d;\
										CHARACTER_BID=%d;\
										CHARACTER_X=%.0f;\
										CHARACTER_Y=%.0f;\
										CHARACTER_LOCATION_ID=%d;\
										",
										Dialog, //EVENT_TYPE
										PacketGetInt(inPacket, 5), //DIALOG_ID
										currentNPC->id, //NPC_ID
										clients[ci]->character->id,
										clients[ci]->character->base->id,
										clients[ci]->character->x,
										clients[ci]->character->y,
										clients[ci]->character->currentLocation->id
										);
									luaL_dostring(luaState, str);
									luaL_dofile(luaState, currentNPC->base->path);
								}
							}
							else
							{
								Log(Warning, "Client requested dialog with NPC which is not exist in current location (or absolutely)");
							}
							break;
						}
						case ItemPickUp:
						{
							CurrentItem* currentItem = clients[ci]->character->currentLocation->GetItem(PacketGetInt(inPacket, 1));
							if (currentItem)
							{
								f32 distance = vector2d<f32>(currentItem->x, currentItem->y).getDistanceFrom(vector2d<f32>(clients[ci]->character->x, clients[ci]->character->y));
								if (distance < 3.0f)
								{
									CurrentItem* currentItemClone = new CurrentItem(*currentItem);

									//Inform all CurrentCharacters that CurrentItem was unspawned
									CreatePacket(outPacket, ItemUnspawned, "%i%b",
										currentItem->id,
										Ground
										);
									for (int i = 0; i < clients[ci]->character->currentLocation->currentCharactersCount; i++)
										clients[ci]->character->currentLocation->currentCharacters[i]->connectSocket->Send(outPacket);
									clients[ci]->character->currentLocation->UnSpawnItem(currentItem);
									
									currentItemClone->owner = clients[ci]->character;
									currentItemClone->currentLocation = NULL;
									currentItemClone->x = 0;
									currentItemClone->y = 0;

									//Inform CurrentCharacter that CurrentItem was spawned in his inventory
									clients[ci]->character->SpawnItem(currentItemClone);
									CreatePacket(outPacket, ItemSpawned, "%i%i%f%f%b%i",
										currentItemClone->id,
										currentItemClone->base->id,
										currentItemClone->x,
										currentItemClone->y,
										Inventory,
										currentItemClone->count
										);
									clients[ci]->character->connectSocket->Send(outPacket);
								}
							}
							break;
						}
					}
				}
				else if (iResult == -1)
				{ //Client disconnected
					if (clients[ci]->character) //Client logged in
					{
						//Save CurrentCharacter's data to DB
						clients[ci]->character->Update();
						//Inform all CurrentCharacters that CurrentCharacter was unspawned
						CreatePacket(outPacket, CharacterUnspawned, "%i", clients[ci]->character->id);
						for (int i = 0; i < clients[ci]->character->currentLocation->currentCharactersCount; i++)
							if (clients[ci]->character->currentLocation->currentCharacters[i] != clients[ci]->character)
							{ //It's not a character, that's unspawning
								clients[ci]->character->currentLocation->currentCharacters[i]->connectSocket->Send(outPacket);
							}
						clients[ci]->character->currentLocation->UnSpawnCharacter(clients[ci]->character);
					}

					delete clients[ci];
					clientsCount--;
					if (ci != clientsCount) //Deleting character is not the last, so we need to 'patch a hole' in array
						clients[ci] = clients[clientsCount];
					clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
					
					printf("Client %d: Disconnected\n", ci);
				}
				else
				{ //Wrong packet from client
					Log(Warning, "Wrong packet from client %d", ci);
				}
			}
		}

		//Simulating world
		
		currentTime = GetTickCount();
		if ((currentTime - lastStepTime) > 100)
		{
			lastStepTime = currentTime; // - ((currentTime - lastStepTime) - 100); //If server is slow
			for (ci = 0; ci < clientsCount; ci++)
			{
				if (clients[ci]->character)
				{
					if (clients[ci]->character->x != clients[ci]->character->movingX || clients[ci]->character->y != clients[ci]->character->movingY)
					{
						if (vector2d<f32>(clients[ci]->character->x, clients[ci]->character->y).getDistanceFrom(vector2d<f32>(clients[ci]->character->movingX, clients[ci]->character->movingY)) > clients[ci]->character->base->speed)
						{
							clients[ci]->character->x += clients[ci]->character->deltaX;
							clients[ci]->character->y += clients[ci]->character->deltaY;
							//printf("%.3f    %.3f\n", clients[ci]->character->x, clients[ci]->character->y);
						}
						else
						{
							clients[ci]->character->x = clients[ci]->character->movingX;
							clients[ci]->character->y = clients[ci]->character->movingY;
							//printf("Came\n");
						}
					}
				}
			}
		}
	}
	
	delete serverSocket;
	delete game;

	system("pause");
}
