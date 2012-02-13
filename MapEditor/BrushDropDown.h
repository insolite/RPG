#pragma once
#include "StringDropDown.h"
#include "Universe.h"

class BrushDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	BrushDropDown(void);
	~BrushDropDown(void);
};
