#include "StdAfx.h"
#include "Universe.h"

Universe* Universe::instance;

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
	int i, j;
	char inPacket[256], outPacket[256];
	int packetLength;
	int iResult;

	continueFlag = true;

	game = new Game("testgame");
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
		for (i = 0; i < clientsCount; i++)
		{
			packetLength = clients[i]->Receive(inPacket);
			if (packetLength > 0)
			{
				printf("Packet received: %c\n", inPacket[0]);
			}
			else
			{
				iResult = WSAGetLastError();
				if (iResult != WSAEWOULDBLOCK && iResult != 0)
				{
					delete clients[i];
					clientsCount--;
					for (j = i; j < clientsCount; j++) //TODO: Put last element in place of deleted, instead of shift?
						clients[j] = clients[j + 1];
					clients = (ServerClientSocket**)realloc(clients, clientsCount * sizeof(ServerClientSocket*));
					printf("Client %d: Socket error: %d\n", i, iResult);
					printf("Client %d: Disconnected\n", i);
					//continueFlag = false; //TEST
				}
			}
		}

		//Simulating world
		//TEST
		for (i = 0; i < clientsCount; i++)
		{
			outPacket[0] = 'a';
			outPacket[1] = '\0';
			clients[i]->Send(outPacket, 2);
		}
		//Sleep(200);
	}
	
	delete serverSocket;
	delete game;

	system("pause");
}
