#include "MapCell.h"
#pragma once

class Location
{
public:
	MapCell** mask;
	int width, height;

	void Load(char* filename);
	void Print();

	Location(void);
	~Location(void);
};

