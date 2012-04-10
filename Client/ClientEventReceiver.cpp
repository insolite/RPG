#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"
#include "ClientEventReceiver.h"

bool ClientEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (KeyIsDown[KEY_ESCAPE])
		{ //Return to the main menu
			delete Universe::instance->login;
			delete Universe::instance->password;
			Universe::instance->login = NULL;
			Universe::instance->password = NULL;
			Universe::instance->state = NextLevel;
		}
	}
	else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		for (s32 i = 0; i < EMIE_COUNT; ++i)
            Mouse[i] = i == event.MouseInput.Event;
		IGUIElement* guiElement = Universe::instance->guienv->getRootGUIElement()->getElementFromPoint(vector2di(event.MouseInput.X, event.MouseInput.Y));
		if (guiElement != NULL)
		{ //Mouse is in a window area
			if (guiElement->getID() != 0) //Mouse is on GUI element
				return false;
		}
		else //Mouse is not in a window area
			return false;
		if (Mouse[EMIE_LMOUSE_LEFT_UP])
		{
			char outPacket[256];
			vector3df position = Universe::instance->render->MouseCoordToWorldCoord();
			int x, y;
			x = position.X / CELL_SIZE;
			y = position.Z / CELL_SIZE;
			CreatePacket(outPacket, Move, "%i%i", x, y);
			Universe::instance->connectSocket->Send(outPacket);
		}
		else if (Mouse[EMIE_MOUSE_WHEEL])
		{
			Universe::instance->cameraY += event.MouseInput.Wheel * 5;
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 eventCallerId = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case RPGATOR_EET_ELEMENT_DRAGGED:
				if (event.GUIEvent.Element)
				{ //Element dragged to an GUI element
					if (event.GUIEvent.Element->getParent())
					{ //Element dragged to an GUI element that has parent (IGUIIconTableContainer)
						if (event.GUIEvent.Element->getParent()->getID() == HotkeyBar)
						{ //Empty cell
							CGUIButton* hotkeyButton = new CGUIButton(*((CGUIButton*)event.GUIEvent.Caller));
							((IGUIIconTable::IGUIIconTableContainer*)event.GUIEvent.Element)->setButton(hotkeyButton);
						}
						else if (event.GUIEvent.Element->getParent()->getParent())
						{ //Element dragged to an GUI element that has parent (IGUIIconTable)
							if (event.GUIEvent.Element->getParent()->getParent()->getID() == HotkeyBar)
							{ //Existing cell
								CGUIButton* hotkeyButton = new CGUIButton(*((CGUIButton*)event.GUIEvent.Caller));
								((IGUIIconTable::IGUIIconTableContainer*)event.GUIEvent.Element->getParent())->setButton(hotkeyButton);
							}
						}
					}
				}
				break;
			case EGET_EDITBOX_ENTER:
				switch (eventCallerId)
				{
					case ChatInputEditBox:
						IGUIElement* eb = Universe::instance->guienv->getRootGUIElement()->getElementFromId(ChatBox)->getElementFromId(ChatInputEditBox);
						if (wcslen(eb->getText()) > 0)
						{
							char outPacket[256];
							char str[256]; //TODO: %ws
							wcstombs(str, eb->getText(), 255);
							CreatePacket(outPacket, Say, "%b%s", Public, str);
							Universe::instance->connectSocket->Send(outPacket);
							eb->setText(NULL);
						}
						break;
				}
				break;
			case EGDT_WINDOW_CLOSE:
				break;
			case EGET_BUTTON_CLICKED:
				switch (eventCallerId)
				{
					case TESTSkillUseButton:
					{
						char outPacket[256];
						CreatePacket(outPacket, SkillUse, "%i", 1);
						Universe::instance->connectSocket->Send(outPacket);
						break;
					}
					case ChatInputEditBox:
						Universe::instance->guienv->getRootGUIElement()->getElementFromId(ChatInputEditBox)->setText(L"");
						break;
				}
				break;
			case EGET_COMBO_BOX_CHANGED:
				break;
			case EGET_TAB_CHANGED:
				break;
			case EGET_CHECKBOX_CHANGED:
				break;
		}
	}

	return false;
}

bool ClientEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool ClientEventReceiver::isMouseDown(EKEY_CODE mouseCode) const
{
	return Mouse[mouseCode];
}

ClientEventReceiver::ClientEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	for (u32 i = 0; i < EMIE_COUNT; ++i)
		Mouse[i] = false;
}
