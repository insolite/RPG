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
	/*
	screenWidth = 1366;
	screenHeight = 768;
	fullscreen = true;
	*/
	instance = this;
	
	render = new Render(screenWidth, screenHeight, fullscreen, L"Client");

	guienv = render->device->getGUIEnvironment();

	gui::IGUIFont* font2 = guienv->getFont("res/font.bmp");
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

	continueFlag = true;

	connectSocket = new ClientSocket("127.0.0.1", "3127");
	printf("Connected to the server\n");
	CreatePacket(outPacket, LogIn, "%s%s", login, password);
	connectSocket->Send(outPacket);

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
				printf("Packet received: '%s'; Length: %d; Ping: %d;\n", inPacket + 2, GetPacketLength(inPacket), 0);
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
					case CharacterUnspawned:
					{
						CurrentCharacter* unspawningCharacter = currentLocation->GetCharacter(PacketGetInt(inPacket, 1));
						//if (currentCharacter == unspawningCharacter)
							//Something's wrong...
						unspawningCharacter->node->remove();
						currentLocation->UnSpawnCharacter(unspawningCharacter);
						break;
					}
					case Say:
					{
						//GOVNOCODE
						IGUIElement* eb = guienv->getRootGUIElement()->getElementFromId(ChatBox)->getElementFromId(ChatEditBox);
						char* str;
						if (PacketGetByte(inPacket, 1) == Private)
							str = PacketGetString(inPacket, 10);
						else
							str = PacketGetString(inPacket, 6);
						//TODO: daat->GetCharacter;
						//for (int i = 0; i < game->data->locationsCount; i++)
						CurrentCharacter* sender = currentLocation->GetCharacter(PacketGetInt(inPacket, 2));
						wchar_t* wstr = new wchar_t[wcslen(eb->getText()) + strlen(str) + strlen(sender->login) + 4];
						wcscpy(wstr, eb->getText());
						wcscat(wstr, L"\n");
						mbstowcs(wstr + wcslen(wstr), sender->login, 2 * strlen(sender->login));
						wcscat(wstr, L": ");
						mbstowcs(wstr + wcslen(wstr), str, 2 * strlen(str));
						eb->setText(wstr);
						//delete wstr;
						break;
					}
					case CharacterMoving:
						//printf("Character #%d is moving to %d %d\n",PacketGetInt(inPacket,1),PacketGetInt(inPacket,5),PacketGetInt(inPacket,9));
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

			if (currentCharacter)
			{
				/*
				Kt.X = currentCharacter->x * CELL_SIZE;
				Km.X = currentCharacter->x * CELL_SIZE;
				camPos->setPosition(Km);
				Kt.Z = currentCharacter->y * CELL_SIZE;
				Km.Z = currentCharacter->y * CELL_SIZE;
				camPos->setPosition(Km);
				*/
			}

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
	IGUIEditBox* eb = guienv->addEditBox(L"1234", rect< s32 >(screenWidth / 2 - 64, screenHeight / 2 - 60, screenWidth / 2 + 64, screenHeight / 2 - 28), true, NULL, PasswordEditBox);
	eb->setPasswordBox(true);
	guienv->addButton(rect< s32 >(screenWidth / 2 - 64, screenHeight / 2 - 20, screenWidth / 2 - 4, screenHeight / 2 + 12), NULL, LogInButton, L"Log in", L"Log in");
	guienv->addButton(rect< s32 >(screenWidth / 2 + 4, screenHeight / 2 - 20, screenWidth / 2 + 64, screenHeight / 2 + 12), NULL, RegisterButton, L"Register", L"Register");
}

void Universe::ClientGUIInit()
{
	clientEventReceiver = new ClientEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)clientEventReceiver);

	guienv->addButton(rect< s32 >(0, 0, 256, 32), NULL, TESTSkillUseButton, L"Use skill SayHello", NULL);

	//Chat
	//IGUIStaticText* chatStaticText = guienv->addStaticText(NULL, rect< s32 >(0, 128, 256, 128 + 256), true, true, NULL, ChatStaticText, true);
	//chatStaticText->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	//IGUIEditBox* chatEditBox = guienv->addEditBox(NULL, rect< s32 >(0, 128, 256, 128 + 256), true, NULL, ChatEditBox);
	//chatEditBox->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	//chatEditBox->setMultiLine(true);
	//guienv->addEditBox(NULL, rect< s32 >(0, 128 + 256, 256, 128 + 256 + 24), true, NULL, ChatInputEditBox);
	//ChatEditBox
	//ChatInputEditBox
	IGUIChatBox* cb = new IGUIChatBox(guienv, NULL, ChatBox, ChatEditBox, ChatInputEditBox, rect< s32 >(0, 128, 256, 128 + 256 + 24));
	guienv->getRootGUIElement()->addChild(cb);

	/*
	for (u32 i = 0; i < EGDC_COUNT; i++)
	{
		SColor color = guienv->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		color.setAlpha(48);
		guienv->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, color);
	}
	*/

	//Inventory
	IGUIIconTable* tbl1 = new IGUIIconTable(guienv, NULL, -1, rect< s32 >(screenWidth - 32 * 6, 150, screenWidth, 150 + 32 * 6), 6, 6);
	tbl1->buttonSize = 32;
	guienv->getRootGUIElement()->addChild(tbl1);
	for (int i = 0; i < 36; i++)
		tbl1->addButton();

	//Hotkey
	IGUIIconTable* tbl2 = new IGUIIconTable(guienv, NULL, -1, rect< s32 >(200, screenHeight - 48, 200 + 12 * 48, screenHeight), 12, 1);
	guienv->getRootGUIElement()->addChild(tbl2);
	for (int i = 0; i < 12; i++)
		tbl2->addButton(Universe::instance->render->driver->getTexture("rpgator.png"));
	//IGUIButton* btn = guienv->addButton();
	//btn->setImage();
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
