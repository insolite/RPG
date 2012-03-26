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
	//TEST Lua
	lua_State* L = luaL_newstate();
	
	luaL_dostring(L, "a = 10 + 5");
	lua_getglobal(L, "a");
	int i = lua_tointeger(L, -1);
	printf("%d\n", i);
	
	lua_close(L);
	/*
	int iErr = 0;
	lua_State *lua = lua_open(2);  // Open Lua
	luaopen_io (lua);              // Load io library
	if ((iErr = luaL_loadfile (lua, "test.lua")) == 0)
	{
	   // Call main...
	   if ((iErr = lua_pcall (lua, 0, LUA_MULTRET, 0)) == 0)
	   { 
		  // Push the function name onto the stack
		  lua_pushstring (lua, "helloWorld");
		  // Function is located in the Global Table
		  lua_gettable (lua, LUA_GLOBALSINDEX);  
		  lua_pcall (lua, 0, 0, 0);
	   }
	}
	lua_close (lua);
	*/

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
					}
				}
				else if (iResult == -1)
				{//Client disconnected
					if (clients[ci]->character)
					{
						//TODO: data->UnspawnCharacter(clients[ci]->character)
						delete clients[ci]->character;
					}

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
		Sleep(20);
	}
	
	delete serverSocket;
	delete game;

	system("pause");
}
