#include "StdAfx.h"
#include "ToggleWindowVisibilityButton.h"

void ToggleWindowVisibilityButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	window->setVisible(!window->isVisible());
}

ToggleWindowVisibilityButton::ToggleWindowVisibilityButton(char* label, gcn::Window* _window) : Button(label)
{
	window = _window;
}

ToggleWindowVisibilityButton::~ToggleWindowVisibilityButton(void)
{
}
