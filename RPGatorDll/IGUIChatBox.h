#pragma once

class __declspec(dllexport) IGUIChatBox :
	public IGUIElement
{
public:
	void draw();

	IGUIChatBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id, s32 editBoxId, s32 chatInpuId, core::rect<s32> rectangle);
	~IGUIChatBox(void);
};
