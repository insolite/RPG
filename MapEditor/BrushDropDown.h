#pragma once
#include "stringdropdown.h"

class BrushDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	BrushDropDown(Universe* _universe);
	~BrushDropDown(void);
};
