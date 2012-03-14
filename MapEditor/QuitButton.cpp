#include "StdAfx.h"
#include "QuitButton.h"

QuitButton::QuitButton(std::string label) : Button(label)
{
}

QuitButton::~QuitButton(void)
{
}

void QuitButton::mouseClicked(gcn::MouseEvent& mouseEvent)
{
	*continueFlag = 2;
}
