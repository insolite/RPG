#pragma once
#include "StringListModel.h"
#include "MapObject.h"
#include "Universe.h"

//TODO: temp
#include "MenuButton.h"

class MapObjectSelectWindow :
	public gcn::Window
{
public:
	gcn::CheckBox** mapObjectsTags;
	int tagsCount;
	StringListModel* listModel;
	gcn::ListBox* listBox;
	gcn::ScrollArea* listBoxScrollArea;
	gcn::Icon* npcPreviewIcon;
	MenuButton* okButton;

	MapObjectSelectWindow(std::string caption, MapObject** mapObjects, int mapObjectsCount);
	~MapObjectSelectWindow(void);
};

