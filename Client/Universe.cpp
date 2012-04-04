#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MenuEventReceiver.h"
#include "ClientEventReceiver.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	screenWidth = 800;
	screenHeight = 600;
	fullscreen = false;
	instance = this;
	
	render = new Render(screenWidth, screenHeight, L"Client");

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
	Universe::instance->login = NULL;
	Universe::instance->password = NULL;

	MenuGUIInit();
	
	state = Continue;
	while (render->device->run() && state == Continue)
	{
		render->driver->beginScene(true, true, SColor(255, 100, 101, 140));
			guienv->drawAll();
		render->driver->endScene();
	}

	MenuGUIDestroy();

	if (Universe::instance->login)
		return false;

	return true;
}

void Universe::DrawScene()
{//TEST
	int i, j, drawWidth, drawHeight;

	//for (i = 0; i < currentLocation->height; i++)
	for (i = 0; i < currentLocation->height; i++)
	{
		//for (j = 0; j < currentLocation->width; j++)
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j]->cellProperty)
			{
				case Free:
					render->drawKub(j*CELL_SIZE,-20,i*CELL_SIZE);
					break;
				/*case Locked:
					glColor4d(1, 0, 0, 0.5);
					break;
				default:
					glColor4d(1, 1, 1, 1);*/
			}
			/*glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize + cellSize);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize + cellSize);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize);
			glEnd();*/
		}
	}
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
	CreatePacket(outPacket, LogIn, "%s%s", login, password);
	connectSocket->Send(outPacket);

	ping = SDL_GetTicks(); //TEST

	game = NULL;
	currentCharacter = NULL;
	
	ClientGUIInit();

	//variables for camera
	ISceneNode* camPos=render->smgr->addEmptySceneNode();
	camPos->setPosition(vector3df(50,50,10));
	camera=render->smgr->addCameraSceneNode(0, vector3df(50,50,10), vector3df(50,0,40));
	camera2=render->smgr->addCameraSceneNode(0, vector3df(0,50,-20), vector3df(0,0,0));
	render->smgr->setActiveCamera(camera);
	
	state = Continue;

	while (render->device->run() && state == Continue)
	{
		//Receving packet from the server
		iResult = connectSocket->Receive(inPacket);
		if (iResult)
		{
			if (iResult > 0)
			{ //Packet received
				printf("Packet received: '%s'; Length: %d; Ping: %d;\n", inPacket + 2, GetPacketLength(inPacket), SDL_GetTicks() - ping);
				ping = SDL_GetTicks();
				switch (GetPacketType(inPacket))
				{
					case LoggedIn:
						game = new Game(inPacket + 3, Client);
						printf("Game %s initialized\n", game->name);
						currentLocation = game->data->GetLocation(PacketGetInt(inPacket, 1 + strlen(inPacket + 3) + 1));
						DrawScene();
						render->drawKub(0,0,0);
						break;
					case CharacterSpawned:
						if (!currentCharacter)
						{
							currentCharacter = new CurrentCharacter(inPacket);
							currentLocation->SpawnCharacter(currentCharacter);
						}
						else
						{
							currentLocation->SpawnCharacter(new CurrentCharacter(inPacket));
						}
						break;
					case Say:
						printf("Message: %s\n", PacketGetString(inPacket, 6));
						break;
					case CharacterMoving:
						printf("Character #%d is moving to %d %d\n",PacketGetInt(inPacket,1),PacketGetInt(inPacket,5),PacketGetInt(inPacket,9));
						render->moveNode(currentLocation->GetCharacter(PacketGetInt(inPacket,1))->node, vector3df(PacketGetInt(inPacket,5) * CELL_SIZE, 0, PacketGetInt(inPacket,9) * CELL_SIZE));
						
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
			{ //Disconnected from the server
				printf("Disconnected from the server\n");
				delete Universe::instance->login;
				delete Universe::instance->password;
				Universe::instance->login = NULL;
				Universe::instance->password = NULL;
				Universe::instance->state = NextLevel;
			}
			else
			{ //Wrong packet from the client
				printf("Warning! Wrong packet from server. Error code: %d\n", iResult);
			}
		}

		//Drawing

		if (game)
		{
			core::vector3df Km = camPos->getPosition();
			Kt = camera->getTarget();
		
			if(clientEventReceiver->IsKeyDown(irr::KEY_LEFT))
			{
				Kt.X-=3;
				Km.X-=3;
				camPos->setPosition(Km);
			}
			if(clientEventReceiver->IsKeyDown(irr::KEY_RIGHT))
			{
				Kt.X+=3;
				Km.X+=3;
				camPos->setPosition(Km);
			}
			if(clientEventReceiver->IsKeyDown(irr::KEY_UP))
			{
				Kt.Z+=3;
				Km.Z+=3;
				camPos->setPosition(Km);
			}
			if(clientEventReceiver->IsKeyDown(irr::KEY_DOWN))
			{
				Kt.Z-=3;
				Km.Z-=3;
				camPos->setPosition(Km);
			}
			//camera->setPosition(Km)
			camera->setPosition(Km);
			camera->setTarget(Kt);

			render->driver->beginScene(true, true, SColor(255,100,101,140));
				render->smgr->drawAll();
				guienv->drawAll();
			render->driver->endScene();
		}
	}

	ClientGUIDestroy();

	delete connectSocket;
	if (game)
	{
		delete game;
		render->smgr->clear();
	}

	if (state == NextLevel)
		return false;
	return true;
}

void Universe::MenuGUIInit()
{
	menuEventReceiver = new MenuEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)menuEventReceiver);

	guienv->addEditBox(L"admin", rect< s32 >(screenWidth / 2 - 64, screenHeight / 2 - 100, screenWidth / 2 + 64, screenHeight / 2 - 68), true, NULL, LoginEditBox);
	guienv->addEditBox(L"1234", rect< s32 >(screenWidth / 2 - 64, screenHeight / 2 - 60, screenWidth / 2 + 64, screenHeight / 2 - 28), true, NULL, PasswordEditBox);
	guienv->addButton(rect< s32 >(screenWidth / 2 - 64, screenHeight / 2 - 20, screenWidth / 2 - 4, screenHeight / 2 + 12), NULL, LogInButton, L"Log in", L"Log in");
	guienv->addButton(rect< s32 >(screenWidth / 2 + 4, screenHeight / 2 - 20, screenWidth / 2 + 64, screenHeight / 2 + 12), NULL, RegisterButton, L"Register", L"Register");
}

void Universe::ClientGUIInit()
{
	clientEventReceiver = new ClientEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)clientEventReceiver);

	guienv->addButton(rect< s32 >(0, 0, 256, 32), NULL, TESTSkillUseButton, L"Use skill SayHello", NULL);
}

void Universe::MenuGUIDestroy()
{
	guienv->clear();
	delete menuEventReceiver;
}

void Universe::ClientGUIDestroy()
{
	guienv->clear();
	delete clientEventReceiver;
}
