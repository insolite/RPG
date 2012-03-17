#pragma once
#include "MapObject.h"

class Item :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//Item(int _id);
	__declspec(dllexport) Item(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~Item(void);
};
