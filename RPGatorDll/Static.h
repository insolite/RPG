#pragma once
#include "BrushMask.h"
#include "MapObject.h"

class Static :
	public MapObject
{
public:	
	BrushMask* mask;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//Static(int _id);
	__declspec(dllexport) Static(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~Static(void);
};
