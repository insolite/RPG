#pragma once
#include "MapCell.h"

class Location
{
public:
	MapCell*** mask;
	int width, height;
	int id;
	char *name;

	bool Init(char* gameName, int id);
	void Print();

	Location(void);
	~Location(void);
};

