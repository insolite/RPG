#pragma once
#include "StringListModel.h"
#include "MapObject.h"
#include "Universe.h"
#include "MapObjectSelectOKButton.h"
#include "ToggleWindowVisibilityButton.h"
#include "FocusingWindow.h"

class MapObjectSelectWindow :
	public FocusingWindow
{
public:
	int brushIndex; //TODO: typeof would be fine...
	MapObject** mapObjects;
	gcn::CheckBox** mapObjectsTags;
	int tagsCount;
	StringListModel* listModel;
	gcn::ListBox* listBox;
	gcn::ScrollArea* listBoxScrollArea;
	gcn::Icon* npcPreviewIcon;
	gcn::Button* okButton;
	gcn::Button* closeButton;

	MapObjectSelectWindow(std::string caption, MapObject** _mapObjects, int mapObjectsCount, int brushIndex);
	~MapObjectSelectWindow(void);
};

