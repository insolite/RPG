#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\widgets\dropdown.hpp"
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
