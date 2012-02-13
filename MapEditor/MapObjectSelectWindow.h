#pragma once
#include "StringListModel.h"
#include "MapObject.h"
#include "Universe.h"
#include "MapObjectSelectOKButton.h"
#include "WindowCloseButton.h"
#include "FocusingWindow.h"

class MapObjectSelectWindow :
	public FocusingWindow
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
	gcn::Button* closeButton;

	MapObjectSelectWindow(std::string caption, MapObject** _mapObjects, int mapObjectsCount);
	~MapObjectSelectWindow(void);
};

