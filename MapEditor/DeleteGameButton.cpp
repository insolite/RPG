#include "StdAfx.h"
#include "DeleteGameButton.h"
#include "StringListModel.h"

DeleteGameButton::DeleteGameButton(std::string label, gcn::ListBox* _gamesListBox) : Button(label)
{
	gamesListBox = _gamesListBox;
}

DeleteGameButton::~DeleteGameButton(void)
{
}

void DeleteGameButton::mouseClicked(gcn::MouseEvent& mouseEvent)
{
	if (!(gamesListBox->getSelected() >= gamesListBox->getListModel()->getNumberOfElements()))
	{
		char path[262];

		sprintf(path, "game/%s", ((StringListModel*)gamesListBox->getListModel())->getElementAt(gamesListBox->getSelected()).c_str());
		ClearDir(path);
		RemoveDirectory(path);
		((StringListModel*)gamesListBox->getListModel())->remove(gamesListBox->getSelected());
	}
}
