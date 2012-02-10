#pragma once
#include "stringdropdown.h"

class FloorDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	FloorDropDown(Universe* _universe);
	~FloorDropDown(void);
};
