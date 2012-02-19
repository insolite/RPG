#pragma once
#include "MapObject.h"
#include "BrushMask.h"

class Static :
	public MapObject
{
public:	
	BrushMask* mask;

	void Abstr(void) { }; //Abstract class inheritance

	//Static(int _id);
	Static(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	~Static(void);
};
