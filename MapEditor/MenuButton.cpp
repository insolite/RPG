#include "StdAfx.h"
#include "MenuButton.h"

void MenuButton::mouseMoved(gcn::MouseEvent &mouseEvent)
{
	//printf("Moved: %d\n", mouseEvent.getButton());
}

void MenuButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	printf("Clicked: %d\n", mouseEvent.getButton());
}

MenuButton::MenuButton(char* label) : Button(label)
{
	addMouseListener(this);
}
