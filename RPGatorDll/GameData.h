#pragma once

class __declspec(dllexport) GameData
{
public:
	Location** locations;
	int locationsCount;

	void LocationsInit(InitializationType initializationType);
	Location* GetLocation(int id);
	int AddLocation(char* name, int width, int height);
	void LocationSpawn(SqliteResult sqliteResult, InitializationType initializationType);
	void LocationSpawn(int id, InitializationType initializationType);
	void LocationDelete(int i);
	CurrentNPC* GetNPC(int id);
	CurrentStatic* GetStatic(int id);
	CurrentItem* GetItem(int id);
	CurrentCharacter* GetCharacter(int id);

	GameData(InitializationType initializationType);
	~GameData(void);
};
