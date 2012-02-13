#pragma once
#include "MapCell.h"

class Location
{
public:
	MapCell*** mask;
	int width, height;
	int id;
	char *name;

	Location(int _id);
	~Location(void);
};
