#include "StdAfx.h"
#include "MapObjectSelectOKButton.h"

MapObjectSelectOKButton::MapObjectSelectOKButton(char* label) : Button(label)
{
}

MapObjectSelectOKButton::~MapObjectSelectOKButton(void)
{
}

void MapObjectSelectOKButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	MapObjectSelectWindow* parent = (MapObjectSelectWindow*)this->getParent();
	Universe::instance->brush[Universe::instance->brushIndex] = parent->mapObjects[parent->listBox->getSelected()];
	parent->setVisible(false);
}
