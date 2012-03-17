#include "StdAfx.h"
#include "MapCell.h"

MapCell::MapCell(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : MapObject(strings, integers)
{
	cellProperty = (CellProperty)integers["cellProperty"];
}

MapCell::~MapCell(void)
{
}
