#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "EditorEventReceiver.h"
#include "Render.h"
#include "Universe.h"
#include "MenuEventReceiver.h"

// наш собственный обработчик событий
bool MenuEventReceiver::OnEvent(const SEvent& event)
{
	// просто запоминаем состояние любой клавиши - нажата/отжата
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
		s32 id = event.GUIEvent.Caller->getID(); // получаем идентификатор элемента, вызвавшего событие

		switch(event.GUIEvent.EventType) // обрабатываем события относительно типа
		{
			case EGET_BUTTON_CLICKED:
				//if (id == QuitButton)
				if (id == LoadGameButton)
				{
					Universe::instance->gameName = new char[256];
					wcstombs(Universe::instance->gameName, Universe::instance->lb->getListItem(Universe::instance->lb->getSelected()), 255);
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
