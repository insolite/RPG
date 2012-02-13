#include "StdAfx.h"
#include "WindowCloseButton.h"

WindowCloseButton::WindowCloseButton(char* label) : Button(label)
{
}

WindowCloseButton::~WindowCloseButton(void)
{
}

void WindowCloseButton::Dock()
{
	this->setPosition(this->getParent()->getWidth() - this->getWidth(), 0); // this->getParent()->getHeight() - this->getHeight()
}

void WindowCloseButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	this->getParent()->setVisible(false);
}
