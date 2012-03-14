#include "StdAfx.h"
#include "LoadGameButton.h"

LoadGameButton::LoadGameButton(std::string label) : Button(label)
{
}

LoadGameButton::~LoadGameButton(void)
{
}

void LoadGameButton::mouseClicked(gcn::MouseEvent& mouseEvent)
{
	*continueFlag = 0;
}
