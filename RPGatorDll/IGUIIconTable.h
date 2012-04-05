#pragma once

class IGUIIconTable :
	public IGUIElement
{
public:
	int width;
	int height;
	int buttonSize;

	__declspec(dllexport) void draw();
	__declspec(dllexport) void addButton(ITexture* image = NULL, int localId = -1, const wchar_t* text = NULL, const wchar_t* tooltiptext = NULL);
	__declspec(dllexport) void removeButton(IGUIButton* button);

	__declspec(dllexport) IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height);
	__declspec(dllexport) ~IGUIIconTable(void);
};
