#pragma once

class MenuEventReceiver :
	public IEventReceiver
{
public:
	Game* game;

	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	MenuEventReceiver();
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};
