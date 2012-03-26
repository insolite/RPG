#pragma once
#include "ToggleWindowVisibilityButton.h"

class ClosableWindow :
	public gcn::Window
{
public:
	ToggleWindowVisibilityButton* closeButton;

	ClosableWindow(std::string caption);
	~ClosableWindow(void);
};
