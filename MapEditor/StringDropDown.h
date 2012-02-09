#pragma once
#include "Universe.h"

class StringDropDown :
	public gcn::DropDown
{
public:
	void add(std::string str);

	StringDropDown(Universe* _universe);
	~StringDropDown(void);

protected:
	Universe* universe;
};
