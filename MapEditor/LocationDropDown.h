#pragma once
#include "stringdropdown.h"
class LocationDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	LocationDropDown(Universe* _universe);
	~LocationDropDown(void);
};

