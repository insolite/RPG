#pragma once
#include "Location.h"
#include "utilities.h"

class GameData
{
public:
	Location** locations;
	int locationsCount;
	sqlite3* db;

	__declspec(dllexport) bool LocationsInit();
	__declspec(dllexport) void MapObjectsInit();

	__declspec(dllexport) GameData(void);
	__declspec(dllexport) ~GameData(void);
};
