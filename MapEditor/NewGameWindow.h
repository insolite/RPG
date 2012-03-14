#pragma once
#include "ToggleWindowVisibilityButton.h"
#include "NewGameOKButton.h"

class NewGameWindow :
	public gcn::Window
{
public:
	NewGameOKButton* okButton;
	ToggleWindowVisibilityButton* closeButton;
	gcn::TextField* gameName;
	gcn::TextField* mapWidth;
	gcn::TextField* mapHeight;

	NewGameWindow(std::string caption);
	~NewGameWindow(void);
};
