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
	
	MapObjectSelectTabContainer(gcn::Window* window);
	~MapObjectSelectTabContainer(void);
};

