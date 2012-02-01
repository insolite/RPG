#include "MapCell.h"
#pragma once

class Location
{
public:
	MapCell** mask;
	int width, height;

	void Load(char* filename);

	Location(void);
	~Location(void);
};

