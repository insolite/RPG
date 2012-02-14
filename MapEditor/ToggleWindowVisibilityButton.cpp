#include "StdAfx.h"
#include "ToggleWindowVisibilityButton.h"

void ToggleWindowVisibilityButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	window->setVisible(!window->isVisible());
}

void ToggleWindowVisibilityButton::Dock()
{
	this->setPosition(this->getParent()->getWidth() - this->getWidth(), 0); // this->getParent()->getHeight() - this->getHeight()
}

ToggleWindowVisibilityButton::ToggleWindowVisibilityButton(char* label, gcn::Window* _window) : Button(label)
{
	window = _window;
}

ToggleWindowVisibilityButton::~ToggleWindowVisibilityButton(void)
{
}
