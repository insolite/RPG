#pragma once
#include "ToggleWindowVisibilityButton.h"

class NewGameWindow :
	public gcn::Window
{
public:
	gcn::Button* okButton;
	gcn::Button* closeButton;

	NewGameWindow(std::string caption);
	~NewGameWindow(void);
};
