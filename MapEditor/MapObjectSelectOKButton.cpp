#include "StdAfx.h"
#include "MapObjectSelectOKButton.h"

Universe* Universe::instance;

MapObjectSelectOKButton::MapObjectSelectOKButton(char* label) : Button(label)
{
}

MapObjectSelectOKButton::~MapObjectSelectOKButton(void)
{
}

void MapObjectSelectOKButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	MapObjectSelectWindow* parent = (MapObjectSelectWindow*)this->getParent();
	Universe::instance->brush[parent->brushIndex] = parent->mapObjects[parent->listBox->getSelected()];
	parent->setVisible(false);
}
