#pragma once
#include "MapObject.h"

class Static :
	public MapObject
{
public:
	void Abstr ( void ) { }; //Abstract class inheritance

	Static(void);
	~Static(void);
};
