#include "StdAfx.h"
#include "StringDropDown.h"

StringDropDown::StringDropDown(void)
{
	this->setListModel(new StringListModel());
	this->setFocusable(false);
}

StringDropDown::~StringDropDown(void)
{
	delete (StringListModel*)getListModel();
}

void StringDropDown::add(std::string str)
{
	((StringListModel*)getListModel())->add(str);
}
