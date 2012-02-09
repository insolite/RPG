#include "StdAfx.h"
#include "StringDropDown.h"
#include "StringListModel.h"

StringDropDown::StringDropDown(Universe* _universe)
{
	this->setListModel(new StringListModel());
	universe = _universe;
	this->setFocusable(false);
}

StringDropDown::~StringDropDown(void)
{
	delete (StringListModel*)getListModel();
}

void StringDropDown::add( std::string str )
{
	((StringListModel*)getListModel())->add(str);
}
