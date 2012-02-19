#include "StdAfx.h"
#include "NewGameWindow.h"

NewGameWindow::NewGameWindow(std::string caption) : Window(caption)
{
	closeButton = new ToggleWindowVisibilityButton("Cancel", this);
	this->add(closeButton, 320, 240);
	this->setSize(320, 256);
	this->setVisible(false);
}

NewGameWindow::~NewGameWindow(void)
{
	delete closeButton;
}
