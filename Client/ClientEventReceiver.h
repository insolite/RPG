#pragma once

class ClientEventReceiver :
	public IEventReceiver
{
public:
	// наш собственный обработчик событий
	virtual bool OnEvent(const SEvent& event);
	// метод возвращающий состояние для запрошенной клавиши
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	//конструктор, в цикле сбрасываем статус для всех клавиш
	ClientEventReceiver();
private:
	// массив для хранения статусов клавиш
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
