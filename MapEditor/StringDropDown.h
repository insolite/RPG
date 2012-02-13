#pragma once
#include "StringListModel.h"

class StringDropDown :
	public gcn::DropDown
{
public:
	void add(std::string str);

	StringDropDown(void);
	~StringDropDown(void);
};
