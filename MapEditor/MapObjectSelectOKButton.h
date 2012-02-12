#pragma once
#include "MapObjectSelectWindow.h"
#include "Universe.h"

class MapObjectSelectOKButton :
	public gcn::Button
{
public:
	//TODO:
	//mapObjects here

	void mouseClicked(gcn::MouseEvent &mouseEvent);

	MapObjectSelectOKButton(char* label);
	~MapObjectSelectOKButton(void);
};
