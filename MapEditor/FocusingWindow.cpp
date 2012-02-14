#include "StdAfx.h"
#include "FocusingWindow.h"
#include "Universe.h"

FocusingWindow::FocusingWindow(std::string caption) : Window(caption)
{
}

FocusingWindow::~FocusingWindow(void)
{
}

void FocusingWindow::mouseEntered(gcn::MouseEvent &mouseEvent)
{
	this->requestFocus();
}

void FocusingWindow::mouseExited(gcn::MouseEvent &mouseEvent)
{
	Universe::instance->editAreaContainer->requestFocus();
}
