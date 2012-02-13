#include "StdAfx.h"
#include "FocusingWindow.h"

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
