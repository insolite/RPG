#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MenuEventReceiver.h"
#include "EditorEventReceiver.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	screenWidth = 800;
	screenHeight = 600;
	fullscreen = false;
	instance = this;
	
	render = new Render(screenWidth, screenHeight);

	guienv = render->device->getGUIEnvironment();

	gui::IGUIFont* font2 = guienv->getFont("editor/font.bmp");
	guienv->getSkin()->setFont(font2);
}

Universe::~Universe(void)
{
	instance = NULL;
}

bool Universe::Menu()
{
	Universe::instance->gameName = NULL;

	MenuGUIInit();
	
	state = Continue;
	while (render->device->run() && state == Continue)
	{
		render->driver->beginScene(true, true, SColor(255, 100, 101, 140));
			guienv->drawAll();
		render->driver->endScene();
	}

	MenuGUIDestroy();

	if (Universe::instance->gameName)
		return false;

	return true;
}

bool Universe::Run()
{
	bool continueFlag; //Continue game or not
	char inPacket[256]; //Holds the input packet
	char outPacket[256]; //Holds the output packet
	int iResult; //The result of 'Receive' and 'Send'
	int ping; //TEST

	continueFlag = true;

	connectSocket = new ClientSocket("127.0.0.1", "3127");
	printf("Connected to the server\n");
	CreatePacket(outPacket, LogIn, "%s%s", "admin", "1234");
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
							currentLocation->AddCharacter(currentCharacter);
						}
						else
						{
							currentLocation->AddCharacter(new CurrentCharacter(inPacket));
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
			}
		}

		system("pause");
		CreatePacket(outPacket, SkillUse, "%i", 1);
		connectSocket->Send(outPacket);
		Sleep(200);
	}

	delete connectSocket;
	delete game;

	if (state == NextLevel)
		return false;
	return true;
}

void Universe::MenuGUIInit()
{
	menuEventReceiver = new MenuEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)menuEventReceiver);
}

void Universe::EditorGUIInit()
{
	editorEventReceiver = new EditorEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)editorEventReceiver);


}

void Universe::MenuGUIDestroy()
{
	guienv->clear();
	delete menuEventReceiver;
}

void Universe::EditorGUIDestroy()
{
	guienv->clear();
	delete editorEventReceiver;
}
