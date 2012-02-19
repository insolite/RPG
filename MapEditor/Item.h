#pragma once
#include "MapObject.h"

class Item :
	public MapObject
{
public:
	void Abstr(void) { }; //Abstract class inheritance

	//Item(int _id);
	Item(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	~Item(void);
};
