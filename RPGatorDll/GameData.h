#pragma once

class GameData
{
public:
	Location** locations;
	int locationsCount;

	__declspec(dllexport) void LocationsInit(InitializationType initializationType);
	__declspec(dllexport) Location* GetLocation(int id);
	__declspec(dllexport) int AddLocation(char* name, int width, int height);
	__declspec(dllexport) void LocationSpawn(SqliteResult sqliteResult, InitializationType initializationType);
	__declspec(dllexport) void LocationSpawn(int id, InitializationType initializationType);
	__declspec(dllexport) void LocationDelete(int i);
	__declspec(dllexport) CurrentNPC* GetNPC(int id);
	__declspec(dllexport) CurrentStatic* GetStatic(int id);
	__declspec(dllexport) CurrentItem* GetItem(int id);
	__declspec(dllexport) CurrentCharacter* GetCharacter(int id);

	__declspec(dllexport) GameData(InitializationType initializationType);
	__declspec(dllexport) ~GameData(void);
};
