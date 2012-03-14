#pragma once
#include "Location.h"

class GameData
{
public:
	Location** locations;
	int locationsCount;
	sqlite3* db;

	bool LocationsInit();
	void MapObjectsInit();

	GameData(void);
	~GameData(void);
};
