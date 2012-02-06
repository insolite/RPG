#include "MapCell.h"
#pragma once

class Location
{
public:
	MapCell** mask;
	int width, height;
	int id;
	char *name;

	bool Init(char* gameName, int id);
	void Print();

	Location(void);
	~Location(void);
};

