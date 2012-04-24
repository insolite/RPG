#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MenuEventReceiver.h"
#include "ClientEventReceiver.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	instance = this;
	
	render = new Render(1366, 768, true, L"Client");

	guienv = render->device->getGUIEnvironment();

	gui::IGUIFont* font2 = guienv->getFont("res/font.xml");
	guienv->getSkin()->setFont(font2);

	SColor color;

	color = guienv->getSkin()->getColor(EGUI_DEFAULT_COLOR::EGDC_3D_FACE);
	color.setAlpha(192);
	guienv->getSkin()->setColor(EGUI_DEFAULT_COLOR::EGDC_3D_FACE, color);
	
	color = guienv->getSkin()->getColor(EGUI_DEFAULT_COLOR::EGDC_3D_SHADOW);
	color.setAlpha(192);
	guienv->getSkin()->setColor(EGUI_DEFAULT_COLOR::EGDC_3D_SHADOW, color);
}

Universe::~Universe(void)
{
	delete menuEventReceiver;
	delete clientEventReceiver;
	delete render;
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
			render->smgr->drawAll();
			guienv->drawAll();
		render->driver->endScene();
	}

	MenuGUIDestroy();

	if (Universe::instance->login)
		return false;

	return true;
}

void Universe::DrawScene()
{
	int i, j, drawWidth, drawHeight;
	/*
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
				case Locked:
					glColor4d(1, 0, 0, 0.5);
					break;
				default:
					glColor4d(1, 1, 1, 1);
			}
		}
	}*/
	render->drawKub(320,-20,320,currentLocation->width,currentLocation->height);
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
	cameraY = 50;
	ISceneNode* camPos=render->smgr->addEmptySceneNode();
	camPos->setPosition(vector3df(50,cameraY,10));
	camera=render->smgr->addCameraSceneNode(0, vector3df(50,50,10), vector3df(50,0,40));

	scene::ISceneNode* lnode; 
	lnode = render->smgr->addLightSceneNode(0,camPos->getPosition(),video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),800.0F);
	render->smgr->setAmbientLight(video::SColor(0,60,60,60));
	
	state = Continue;

	int lastUpdate = render->device->getTimer()->getTime();

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
						break;
					case NPCSpawned:
						currentLocation->SpawnNPC(new CurrentNPC(inPacket));
						break;
					case StaticSpawned:
						currentLocation->SpawnStatic(new CurrentStatic(inPacket));
						break;
					case ItemSpawned:
						switch(PacketGetByte(inPacket, 17))
						{
							case Ground:
								currentLocation->SpawnItem(new CurrentItem(inPacket));
								break;
							case Inventory:
								currentCharacter->SpawnItem(new CurrentItem(inPacket));
								break;
						}
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
					case SkillSpawned:
						currentCharacter->SpawnSkill(new CurrentSkill(inPacket));
						break;
					case NPCUnspawned:
						currentLocation->UnSpawnNPC(currentLocation->GetNPC(PacketGetInt(inPacket, 1)));
						break;
					case StaticUnspawned:
						currentLocation->UnSpawnStatic(currentLocation->GetStatic(PacketGetInt(inPacket, 1)));
						break;
					case ItemUnspawned:
						switch(PacketGetByte(inPacket, 5))
						{
							case Ground:
								currentLocation->UnSpawnItem(currentLocation->GetItem(PacketGetInt(inPacket, 1)));
								break;
							case Inventory:
								//currentCharacter->UnSpawnItem(currentCharacter->GetItem(PacketGetInt(inPacket, 1)));
								break;
						}
						break;
					case CharacterUnspawned:
						currentLocation->UnSpawnCharacter(currentLocation->GetCharacter(PacketGetInt(inPacket, 1)));
						break;
					case Say:
					{
						//GOVNOCODE
						IGUIElement* eb = guienv->getRootGUIElement()->getElementFromId(ChatBox)->getElementFromId(ChatEditBox);
						char* str;
						if (PacketGetByte(inPacket, 1) == Private)
							str = PacketGetString(inPacket, 10);
						else
							str = PacketGetString(inPacket, 6);
						//TODO: data->GetCharacter;
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
					{
						//printf("Character #%d is moving to %d %d\n",PacketGetInt(inPacket,1),PacketGetInt(inPacket,5),PacketGetInt(inPacket,9));
						render->moveNode(currentLocation->GetCharacter(PacketGetInt(inPacket,1))->node, vector3df(PacketGetInt(inPacket,5) * CELL_SIZE, 0, PacketGetInt(inPacket,9) * CELL_SIZE));
						//TEST
						currentCharacter->x = PacketGetInt(inPacket, 5);
						currentCharacter->y = PacketGetInt(inPacket, 9);
						break;
					}
					case DialogOpened:
					{
						char title[256];
						char text[4096];
						wchar_t wstr[512];

						//npcID = PacketGetInt(inPacket, 1);
						//strcpy(title, PacketGetString(inPacket, 5));
						sprintf(title, "[%d] %s", PacketGetInt(inPacket, 1), PacketGetString(inPacket, 5));
						strcpy(text, PacketGetString(inPacket, strlen(PacketGetString(inPacket, 5)) + 5 + 1));

						mbstowcs(wstr, title, 255);
						IGUIWindow* wnd = guienv->addWindow(rect<s32>(256, 128, 256 + 256, 128 + 320), false, wstr, NULL, -1);
						
						char patterns[][256] = {
							"<p\\s+rect\\s*=\\s*\\\"(.*?);(.*?);(.*?);(.*?)\\\">(.*?)</p>",
							"<button\\s+rect\\s*=\\s*\\\"(.*?);(.*?);(.*?);(.*?)\\\"\\s+onclick\\s*=\\s*\\\"(.*?)\\\">(.*?)</button>",
							/*
							"<p>(.*?)</p>",
							"<p>(.*?)</p>",
							"<p>(.*?)</p>",*/
							};
						char** result;
						int patternsCount = 2;
						const char *error;
						int erroffset;
						int count;
						int ovector[30];
						
						const unsigned char *tables = NULL;
						tables = pcre_maketables();

						for (int i = 0; i < patternsCount; i++)
						{
							pcre *re = pcre_compile ((char*)patterns[i], 0, &error, &erroffset, NULL);
							count = pcre_exec(re, NULL, (char*)text, strlen(text), 0, NULL, ovector, 30);
							if (count > 0)
							{
								result = new char*[count];
								for (int c = 0; c < 2 * count; c += 2)
								{
									if (ovector[c] >= 0)
									{
										result[c / 2] = new char[ovector[c + 1] - ovector[c] + 1];
										memcpy(result[c / 2], text + ovector[c], ovector[c + 1] - ovector[c]);
										result[c / 2][ovector[c + 1] - ovector[c]] = '\0';
										//printf("%d, %d\n", ovector[c], ovector[c + 1]);
										//printf("%s\n", result[c / 2]);
									}
									else
									{
										result[c / 2] = NULL;
									}
								}

								switch (i)
								{
									case 0: //p
									{
										wchar_t wstr[1024];
										mbstowcs(wstr, result[5], 1023);
										guienv->addStaticText(wstr, rect<s32>(atoi(result[1]), atoi(result[2]), atoi(result[1]) + atoi(result[3]), atoi(result[2]) + atoi(result[4])), false, true, wnd, DialogElement, false);
										break;
									}
									case 1: //button
									{
										wchar_t wstr[256];
										mbstowcs(wstr, result[6], 255);
										guienv->addButton(rect<s32>(atoi(result[1]), atoi(result[2]), atoi(result[1]) + atoi(result[3]), atoi(result[2]) + atoi(result[4])), wnd, DialogElement + atoi(result[5]), wstr, NULL);
										break;
									}
								}
								
								for (int j = 0; j < count; j++)
									if (result[j])
										delete result[j];
								delete result;
							}
						}
						break;
					}
					case PlayEffect:
					{
						CurrentMapObject<MapObject>* currentMapObject;
						int currentMapObjectId = PacketGetInt(inPacket, 2);
						int skillId = PacketGetInt(inPacket, 6);
						switch (PacketGetByte(inPacket, 1))
						{
							case 0: //NPC
								currentMapObject = (CurrentMapObject<MapObject>*)currentLocation->GetNPC(currentMapObjectId);
								break;
							case 3: //Character
								currentMapObject = (CurrentMapObject<MapObject>*)currentLocation->GetCharacter(currentMapObjectId);
								break;
						}
						render->PlayEffect(currentMapObject->node, game->resources->GetSkill(skillId)->effectTextures);
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

		if ((render->device->getTimer()->getTime() - lastUpdate) > 30)
		{
			lastUpdate = render->device->getTimer()->getTime();
			if (game)
			{
				if (currentCharacter)
				{
					core::vector3df Km = camPos->getPosition();
					render->Kt = camera->getTarget();
					//Kt.X = currentCharacter->x * CELL_SIZE;
					//Kt.Z = currentCharacter->y * CELL_SIZE;
					vector3df pos = currentCharacter->node->getPosition();
					render->Kt.X = pos.X;
					render->Kt.Z = pos.Z;
					Km.X = render->Kt.X;
					Km.Z = render->Kt.Z - 30;
					Km.Y = cameraY;

					camera->setPosition(Km);
					camera->setTarget(render->Kt);

					//vector3df lPos = camera->getPosition();
					vector3df lPos = currentCharacter->node->getPosition();
					lPos.Y = 15;
					//lPos.Z += 20;
					lnode->setPosition(lPos);
				}
				
				

				render->driver->beginScene(true, true, SColor(255,100,101,140));
					render->smgr->drawAll();
					guienv->drawAll();
				render->driver->endScene();
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

	guienv->addEditBox(L"admin", rect< s32 >(render->screenWidth / 2 - 64, render->screenHeight / 2 - 100, render->screenWidth / 2 + 64, render->screenHeight / 2 - 68), true, NULL, LoginEditBox);
	IGUIEditBox* eb = guienv->addEditBox(L"1234", rect< s32 >(render->screenWidth / 2 - 64, render->screenHeight / 2 - 60, render->screenWidth / 2 + 64, render->screenHeight / 2 - 28), true, NULL, PasswordEditBox);
	eb->setPasswordBox(true);
	guienv->addButton(rect< s32 >(render->screenWidth / 2 - 64, render->screenHeight / 2 - 20, render->screenWidth / 2 - 4, render->screenHeight / 2 + 12), NULL, LogInButton, L"Log in", L"Log in");
	guienv->addButton(rect< s32 >(render->screenWidth / 2 + 4, render->screenHeight / 2 - 20, render->screenWidth / 2 + 64, render->screenHeight / 2 + 12), NULL, RegisterButton, L"Register", L"Register");
}

void Universe::ClientGUIInit()
{
	clientEventReceiver = new ClientEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)clientEventReceiver);
	
	int btnsSize = 48;

	//Window toggle buttons
	/*
	IGUIButton* btn;
	btn = guienv->addButton(rect< s32 >(0, render->screenHeight - 32, 64, render->screenHeight), NULL, InventoryToggleButton, L"Inventory", NULL);
	btn->setIsPushButton(true);
	btn = guienv->addButton(rect< s32 >(64, render->screenHeight - 32, 64 + 64, render->screenHeight), NULL, SkillsToggleButton, L"Skills", NULL);
	btn->setIsPushButton(true);
	btn = guienv->addButton(rect< s32 >(64 + 64, render->screenHeight - 32, 64 + 64 + 64, render->screenHeight), NULL, QuestsToggleButton, L"Quests", NULL);
	btn->setIsPushButton(true);
	*/
	IGUIButton* btn;
	btn = guienv->addButton(rect< s32 >(0, render->screenHeight - btnsSize, btnsSize, render->screenHeight), NULL, InventoryToggleButton, NULL, L"Inventory");
	btn->setIsPushButton(true);
	btn->setUseAlphaChannel(true);
	btn->setImage(render->driver->getTexture("res/inventory_icon.png"));
	btn = guienv->addButton(rect< s32 >(btnsSize, render->screenHeight - btnsSize, btnsSize + btnsSize, render->screenHeight), NULL, SkillsToggleButton, NULL, L"Skills");
	btn->setIsPushButton(true);
	btn->setUseAlphaChannel(true);
	btn->setImage(render->driver->getTexture("res/skills_icon.png"));
	btn = guienv->addButton(rect< s32 >(btnsSize + btnsSize, render->screenHeight - btnsSize, btnsSize + btnsSize + btnsSize, render->screenHeight), NULL, QuestsToggleButton, NULL, L"Quests");
	btn->setIsPushButton(true);
	btn->setUseAlphaChannel(true);
	btn->setImage(render->driver->getTexture("res/quests_icon.png"));

	//Chat
	IGUIChatBox* cb = new IGUIChatBox(guienv, NULL, ChatBox, ChatEditBox, ChatInputEditBox, rect< s32 >(0, 128, 256, 128 + 256 + 24));
	guienv->getRootGUIElement()->addChild(cb);

	//Hotkey
	int slotsCount = 9;
	IGUIIconTable* tbl3 = new IGUIIconTable(guienv, NULL, HotkeyBar, rect< s32 >(320, render->screenHeight - btnsSize, 320 + slotsCount * btnsSize + (slotsCount - 1) * 2, render->screenHeight), slotsCount, 1);
	guienv->getRootGUIElement()->addChild(tbl3);
}

void Universe::MenuGUIDestroy()
{
	guienv->clear();
	render->device->setEventReceiver(NULL);
	delete menuEventReceiver;
}

void Universe::ClientGUIDestroy()
{
	guienv->clear();
	render->device->setEventReceiver(NULL);
	delete clientEventReceiver;
}
