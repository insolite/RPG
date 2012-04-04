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
					case LogInButton:
						Universe::instance->login = new char[256];
						Universe::instance->password = new char[256];
						wcstombs(Universe::instance->login, ((IGUIEditBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(LoginEditBox))->getText(), 255);
						wcstombs(Universe::instance->password, ((IGUIEditBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(PasswordEditBox))->getText(), 255);
						Universe::instance->state = NextLevel;
						break;
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
