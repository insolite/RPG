#pragma once
#include "StringListModel.h"
#include "ToggleWindowVisibilityButton.h"

class MapObjectSelectTabContainer :
	public gcn::Container
{
public:
	StringListModel* lastMapCellsListModel;
	gcn::ListBox* lastMapCellsListBox;
	gcn::ScrollArea* lastMapCellsListBoxScrollArea;
	ToggleWindowVisibilityButton* mapCellSelectButton;
	
	MapObjectSelectTabContainer(gcn::Window* window);
	~MapObjectSelectTabContainer(void);
};

