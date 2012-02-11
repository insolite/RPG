#pragma once
#include "MapObject.h"

class Static :
	public MapObject
{
public:
	virtual void Abstr ( void ) = 0; //Abstract class

	Static(void);
	~Static(void);
};
