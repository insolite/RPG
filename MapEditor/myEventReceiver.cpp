#include "StdAfx.h"
using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
        // наш собственный обработчик событий
        virtual bool OnEvent(const SEvent& event)
        {
                // просто запоминаем состояние любой клавиши - нажата/отжата
                if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

                return false;
        }

        // метод возвращающий состояние для запрошенной клавиши
        virtual bool IsKeyDown(EKEY_CODE keyCode) const
        {
                return KeyIsDown[keyCode];
        }
        
        //конструктор, в цикле сбрасываем статус для всех клавиш
        MyEventReceiver()
        {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                        KeyIsDown[i] = false;
        }

private:
        // массив для хранения статусов клавиш
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};