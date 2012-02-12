#include "StdAfx.h"
#include "npcSelectButton.h"
#include "Universe.h"

Universe* Universe::instance;

void NPCSelectButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	Universe::instance->npcSelectWindow->setVisible(!Universe::instance->npcSelectWindow->isVisible());
}

NPCSelectButton::NPCSelectButton(char* label) : Button(label)
{
}

NPCSelectButton::~NPCSelectButton(void)
{
}
