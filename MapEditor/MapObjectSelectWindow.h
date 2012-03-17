#pragma once
#include "StringListModel.h"
#include "Universe.h"
#include "MapObjectSelectOKButton.h"
#include "ToggleWindowVisibilityButton.h"
#include "FocusingWindow.h"
#include "TagCheckBox.h"

class MapObjectSelectWindow :
	public FocusingWindow
{
public:
	int brushIndex; //TODO: typeof would be fine...
	MapObject** mapObjects;
	int mapObjectsCount;
	TagCheckBox** mapObjectsTags;
	int tagsCount;
	StringListModel* listModel;
	gcn::ListBox* listBox;
	gcn::ScrollArea* listBoxScrollArea;
	gcn::Icon* npcPreviewIcon;
	gcn::Button* okButton;

	MapObjectSelectWindow(std::string caption, MapObject** _mapObjects, int mapObjectsCount, int brushIndex);
	~MapObjectSelectWindow(void);
};

