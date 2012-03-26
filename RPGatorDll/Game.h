#pragma once

class Game
{
public:
	char* name;

	static Game* instance;

	sqlite3* db;
	GameResources* resources;
	GameData* data;

	__declspec(dllexport) Game(char* _name, InitializationType initializationType);
	__declspec(dllexport) ~Game(void);
};
