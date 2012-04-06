#pragma once

class IGUIChatBox :
	public IGUIElement
{
public:
	__declspec(dllexport) void draw();

	__declspec(dllexport) IGUIChatBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id, s32 editBoxId, s32 chatInpuId, core::rect<s32> rectangle);
	__declspec(dllexport) ~IGUIChatBox(void);
};

