#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\actionlistener.hpp"
#include "CursorBrush.h"
#include "Universe.h"

//TODO:
//It's better to do with valueChanged() that is in version 0.8.1
class DropDownActionListener :
	public gcn::ActionListener
{
public:
	gcn::DropDown *brushesDropDown, *locationsDropDown;
	Universe* universe;

	void action(const gcn::ActionEvent& actionEvent)
	{
		if (actionEvent.getSource() == brushesDropDown)
		{
			universe->currentBrush = universe->brushes[brushesDropDown->getSelected()];
		}
		else if (actionEvent.getSource() == locationsDropDown)
		{
			universe->SetLocation(universe->locations[locationsDropDown->getSelected()]);
		}
	}

	DropDownActionListener(Universe* _universe);
	~DropDownActionListener(void);
};

