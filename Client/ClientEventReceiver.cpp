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
		else if (KeyIsDown[KEY_RETURN])
		{
			IGUIElement* eb = Universe::instance->guienv->getRootGUIElement()->getElementFromId(ChatInputEditBox);
			if (Universe::instance->guienv->getFocus() == eb)
			{
				if (wcslen(eb->getText()) > 0)
				{
					char outPacket[256];
					char str[256]; //TODO: %ws
					wcstombs(str, eb->getText(), 255);
					CreatePacket(outPacket, Say, "%b%s", Public, str);
					Universe::instance->connectSocket->Send(outPacket);
					eb->setText(NULL);
				}
			}
		}
	}
	else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		for (s32 i = 0; i < EMIE_COUNT; ++i)
            Mouse[i] = i == event.MouseInput.Event;
		if (Mouse[EMIE_LMOUSE_LEFT_UP])
		{
			char outPacket[256];
			vector3df position = Universe::instance->render->mouseToUniverse();
			int x, y;
			x = position.X / CELL_SIZE;
			y = position.Z / CELL_SIZE;
			CreatePacket(outPacket, Move, "%i%i",
				x,
				y
				//Universe::instance->currentCharacter->x,
				//Universe::instance->currentCharacter->y,
				);
			Universe::instance->connectSocket->Send(outPacket);
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 eventCallerId = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
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
