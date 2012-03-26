#pragma once

class GameData
{
public:
	Location** locations;
	int locationsCount;

	__declspec(dllexport) void LocationsInit(InitializationType initializationType);
	__declspec(dllexport) Location* GetLocation(int id);

	__declspec(dllexport) GameData(InitializationType initializationType);
	__declspec(dllexport) ~GameData(void);
};
