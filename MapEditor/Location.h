#pragma once
#include "MapCell.h"
#include "CurrentNPC.h"

class Location
{
public:
	MapCell*** mask; //Not CurrentMapCell
	//CurrentNPC** currentNPCs;
	//CurrentStatic** currentStatics;
	//CurrentItem** currentItems;
	int width, height;
	int id;
	char *name;

	void AddNPC(CurrentNPC* currentNPC); //Factory

	Location(int _id);
	~Location(void);
};
