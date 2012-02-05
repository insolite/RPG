#include "StdAfx.h"
#include "DropDownActionListener.h"


DropDownActionListener::DropDownActionListener(gcn::DropDown* _dropDown, CursorBrush* &_currentBrush, CursorBrush** _brushes)
{
	dropDown = _dropDown;
	currentBrush = &_currentBrush;
	brushes = _brushes;
}


DropDownActionListener::~DropDownActionListener(void)
{
}
