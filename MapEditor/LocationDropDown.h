#pragma once
#include "StringDropDown.h"
#include "Universe.h"

class LocationDropDown :
	public StringDropDown
{
public:
	void valueChanged(const gcn::SelectionEvent &event);

	LocationDropDown(void);
	~LocationDropDown(void);
};

