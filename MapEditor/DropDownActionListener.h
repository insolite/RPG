#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\actionlistener.hpp"
#include "CursorBrush.h"

//TODO:
//It's better to do with valueChanged() that is in version 0.8.1
class DropDownActionListener :
	public gcn::ActionListener
{
public:
	gcn::DropDown* dropDown;
	CursorBrush** currentBrush; //Pointer to pointer
	CursorBrush** brushes;

	void action(const gcn::ActionEvent& actionEvent)
	{
		if (actionEvent.getSource() == dropDown)
		{
			*currentBrush = brushes[dropDown->getSelected()];
		}
	}

	DropDownActionListener(gcn::DropDown* _dropDown, CursorBrush* &_currentBrush, CursorBrush** _brushes);
	~DropDownActionListener(void);
};

