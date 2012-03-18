#include "StdAfx.h"
#include "MapObjectSelectTabContainer.h"


MapObjectSelectTabContainer::MapObjectSelectTabContainer(gcn::Window* window)
{
	//Last MapObjects select ListBox
	lastMapCellsListModel = new StringListModel();
	lastMapCellsListBox = new gcn::ListBox(lastMapCellsListModel);

	//TODO:
	//Auto resize npcSelectListBox. adjustSize doesn't work for width. Sadly...
	lastMapCellsListBox->setSize(176, 0);
	lastMapCellsListBox->adjustSize();
	lastMapCellsListBoxScrollArea = new gcn::ScrollArea();
	lastMapCellsListBoxScrollArea->setHorizontalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	lastMapCellsListBoxScrollArea->setVerticalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	lastMapCellsListBoxScrollArea->setContent(lastMapCellsListBox);
	lastMapCellsListBoxScrollArea->setSize(256, 160);
	
	//MapCells tab container (#1)
	mapCellSelectButton = new ToggleWindowVisibilityButton("Select", window);
	this->add(mapCellSelectButton, 4, 4);
	this->add(lastMapCellsListBoxScrollArea, 4, 36);
	this->setSize(176, 256);
}


MapObjectSelectTabContainer::~MapObjectSelectTabContainer(void)
{
	delete lastMapCellsListModel;
	delete lastMapCellsListBox;
	delete lastMapCellsListBoxScrollArea;
	delete mapCellSelectButton;
}
