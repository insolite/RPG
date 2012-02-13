#pragma once
#include "StringDropDown.h"

class FloorDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	FloorDropDown(void);
	~FloorDropDown(void);
};
