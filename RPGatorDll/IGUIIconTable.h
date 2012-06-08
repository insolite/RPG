#pragma once

class __declspec(dllexport) IGUIIconTable :
	public IGUIElement
{
public:
	int width;
	int height;
	int buttonSize;
	bool Dragging;
	core::position2d<s32> DragStart;
	CGUIButton *selectedButton;

	void draw();
	void addButton(CGUIButton* button);
	void addButton(CurrentGameObject<GameObject>* gameObject, int id);
	CGUIButton* IGUIIconTable::getButtonAt(int index);
	void removeButton(IGUIButton* button, bool shift = true);

	IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height);
	~IGUIIconTable(void);

	class __declspec(dllexport) IGUIIconTableContainer :
		public IGUIElement
	{
	public:
		void draw();
		void setButton(CGUIButton* button);

		IGUIIconTableContainer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);
		~IGUIIconTableContainer(void);
	};
};
