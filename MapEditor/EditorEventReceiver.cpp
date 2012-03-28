#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "MenuEventReceiver.h"
#include "Render.h"
#include "Universe.h"
#include "EditorEventReceiver.h"

// наш собственный обработчик событий
bool EditorEventReceiver::OnEvent(const SEvent& event)
{
	// просто запоминаем состояние любой клавиши - нажата/отжата
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (KeyIsDown[KEY_ESCAPE])
		{
			delete Universe::instance->gameName;
			Universe::instance->gameName = NULL;
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID(); // получаем идентификатор элемента, вызвавшего событие

		switch(event.GUIEvent.EventType) // обрабатываем события относительно типа
		{
			case EGET_BUTTON_CLICKED:
				//if (id == QuitButton)
				{
				}
				break;
		}
	}

	return false;
}

// метод возвращающий состояние для запрошенной клавиши
bool EditorEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
    
//конструктор, в цикле сбрасываем статус для всех клавиш
EditorEventReceiver::EditorEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}
