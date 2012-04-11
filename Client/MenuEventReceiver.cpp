#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"
#include "MenuEventReceiver.h"

bool MenuEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (KeyIsDown[KEY_ESCAPE])
		{
			Universe::instance->render->device->closeDevice();
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 eventCallerId = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				switch (eventCallerId)
				{
					case WindowCloseButton:
						event.GUIEvent.Caller->getParent()->remove();
						break;
					case LogInButton:
						Universe::instance->login = new char[256];
						Universe::instance->password = new char[256];
						wcstombs(Universe::instance->login, ((IGUIEditBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(LoginEditBox))->getText(), 255);
						wcstombs(Universe::instance->password, ((IGUIEditBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(PasswordEditBox))->getText(), 255);
						Universe::instance->state = NextLevel;
						break;
					case RegisterButton:
					{
						IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect<s32>(Universe::instance->render->screenWidth / 2 - 256, Universe::instance->render->screenHeight / 2 - 256, Universe::instance->render->screenWidth / 2 + 256, Universe::instance->render->screenHeight / 2 + 256), false, L"Registration", NULL, RegisterWindow);
						
						Universe::instance->guienv->addEditBox(NULL, rect<s32>(32, 32, 32 + 128, 32 + 32), true, wnd, RegisterWindowLoginEditBox);
						
						IGUIEditBox* pbtn = Universe::instance->guienv->addEditBox(NULL, rect<s32>(32, 72, 32 + 128, 72 + 32), true, wnd, RegisterWindowPasswordEditBox);
						pbtn->setPasswordBox(true);
						
						IGUIComboBox* cb = Universe::instance->guienv->addComboBox(rect<s32>(32, 112, 32 + 128, 112 + 32), wnd, RegisterWindowCharacterRadioButton);
						//TEST
						game = new Game("testgame", Client);
						wchar_t wstr[512];
						for (int i = 0; i < game->resources->charactersCount; i++)
						{
							mbstowcs(wstr, game->resources->characters[i]->name, 255);
							cb->addItem(wstr);
						}

						Universe::instance->guienv->addButton(rect<s32>(512 - 20 - 92, 512 - 20 - 32, 512 - 20, 512 - 20), wnd, RegisterWindowOKButton, L"OK", NULL);
						break;
					}
					case RegisterWindowOKButton:
					{
						char inPacket[256];
						char outPacket[256];
						ClientSocket* connectSocket;
						int iResult; //The result of 'Receive' and 'Send'
						bool continueFlag;

						CreatePacket(outPacket, Register, "%i%ws%ws",
													game->resources->characters[((IGUIComboBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(RegisterWindow)->getElementFromId(RegisterWindowCharacterRadioButton))->getSelected()]->id,
													Universe::instance->guienv->getRootGUIElement()->getElementFromId(RegisterWindow)->getElementFromId(RegisterWindowLoginEditBox)->getText(),
													Universe::instance->guienv->getRootGUIElement()->getElementFromId(RegisterWindow)->getElementFromId(RegisterWindowPasswordEditBox)->getText()
													);
						delete game;

						continueFlag = true;
						connectSocket = new ClientSocket("127.0.0.1", "3127");
						connectSocket->Send(outPacket);
						while (continueFlag) //TODO: timeout
						{
							iResult = connectSocket->Receive(inPacket);
							if (iResult)
							{
								if (iResult > 0)
								{ //Packet received
									switch (GetPacketType(inPacket))
									{
										case RegisterOK:
										{
											IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect<s32>(Universe::instance->render->screenWidth / 2 - 128, Universe::instance->render->screenHeight / 2 - 64, Universe::instance->render->screenWidth / 2 + 128, Universe::instance->render->screenHeight / 2 + 64), false, L"Registration succeeded", NULL, -1);
											Universe::instance->guienv->addButton(rect<s32>(82, 57, 82 + 92, 57 + 32), wnd, WindowCloseButton, L"OK", L"Close this window");
											continueFlag = false;
											break;
										}
										case RegisterFail:
										{
											IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect<s32>(Universe::instance->render->screenWidth / 2 - 128, Universe::instance->render->screenHeight / 2 - 64, Universe::instance->render->screenWidth / 2 + 128, Universe::instance->render->screenHeight / 2 + 64), false, L"Registration failed", NULL, -1);
											Universe::instance->guienv->addButton(rect<s32>(82, 57, 82 + 92, 57 + 32), wnd, WindowCloseButton, L"OK", L"Close this window");
											continueFlag = false;
											break;
										}
									}
								}
								else if (iResult == -1)
								{ //Disconnected from the server
									printf("Disconnected from the server\n");
									continueFlag = false;
								}
								else
								{ //Wrong packet from the client
									printf("Warning! Wrong packet from server. Error code: %d\n", iResult);
									continueFlag = false;
								}
							}
						}
						delete connectSocket;

						Universe::instance->guienv->getRootGUIElement()->getElementFromId(RegisterWindow)->remove();
						break;
					}
				}
				break;
		}
	}

	return false;
}

// метод возвращающий состояние для запрошенной клавиши
bool MenuEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

//конструктор, в цикле сбрасываем статус для всех клавиш
MenuEventReceiver::MenuEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}
