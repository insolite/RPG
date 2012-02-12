#pragma once
#include "StringListModel.h"
#include "MapObject.h"
#include "Universe.h"
#include "MapObjectSelectOKButton.h"

class MapObjectSelectWindow :
	public gcn::Window
{
public:
	MapObject** mapObjects;
	gcn::CheckBox** mapObjectsTags;
	int tagsCount;
	StringListModel* listModel;
	gcn::ListBox* listBox;
	gcn::ScrollArea* listBoxScrollArea;
	gcn::Icon* npcPreviewIcon;
	//MapObjectSelectOKButton* okButton;
	gcn::Button* okButton;

	MapObjectSelectWindow(std::string caption, MapObject** _mapObjects, int mapObjectsCount);
	~MapObjectSelectWindow(void);
};

