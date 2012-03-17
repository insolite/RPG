#include "StdAfx.h"
#include "Item.h"

Item::Item(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : MapObject(strings, integers)
{
	
}

Item::~Item(void)
{
}
