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

	__declspec(dllexport) void AddNPC(CurrentNPC* currentNPC); //Factory

	__declspec(dllexport) Location(int _id);
	__declspec(dllexport) ~Location(void);
};
