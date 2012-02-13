#pragma once
#include "Location.h"

class GameData
{
public:
	Location** locations;
	int locationsCount;

	bool LocationsInit();

	GameData(void);
	~GameData(void);
};
