#include "StdAfx.h"
#include "ClosableWindow.h"

ClosableWindow::ClosableWindow(std::string caption) : gcn::Window(caption)
{
	closeButton = new ToggleWindowVisibilityButton("x");
}

ClosableWindow::~ClosableWindow(void)
{
	delete closeButton;
}
