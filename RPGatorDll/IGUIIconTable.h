#pragma once

class IGUIIconTable :
	public IGUIElement
{
public:
	int width;
	int height;
	int buttonSize;
	bool Dragging;
	core::position2d<s32> DragStart;
	CGUIButton *selectedButton;

	__declspec(dllexport) void draw();
	__declspec(dllexport) void addButton(CGUIButton* button);
	__declspec(dllexport) void addButton(CurrentGameObject<GameObject>* gameObject, int id);
	__declspec(dllexport) CGUIButton* IGUIIconTable::getButtonAt(int index);
	__declspec(dllexport) void removeButton(IGUIButton* button, bool shift = true);

	__declspec(dllexport) IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height);
	__declspec(dllexport) ~IGUIIconTable(void);

	class IGUIIconTableContainer :
		public IGUIElement
	{
	public:
		__declspec(dllexport) void draw();
		__declspec(dllexport) void setButton(CGUIButton* button);

		__declspec(dllexport) IGUIIconTableContainer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);
		__declspec(dllexport) ~IGUIIconTableContainer(void);
	};
};
