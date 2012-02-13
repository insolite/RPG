#pragma once
#include "MapObject.h"

class Item :
	public MapObject
{
public:
	void Abstr ( void ) { }; //Abstract class inheritance

	Item(int _id);
	~Item(void);
};

