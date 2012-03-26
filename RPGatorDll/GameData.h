#pragma once
#include "Location.h"
#include "utilities.h"

class GameData
{
public:
	Location** locations;
	int locationsCount;

	__declspec(dllexport) void LocationsInit();
	__declspec(dllexport) void MapObjectsInit();

	//__declspec(dllexport) 

	__declspec(dllexport) GameData(void);
	__declspec(dllexport) ~GameData(void);
};
