#pragma once

class __declspec(dllexport) Game
{
public:
	char* name;

	static Game* instance;

	sqlite3* db;
	GameResources* resources;
	GameData* data;

	Game(char* _name, InitializationType initializationType);
	~Game(void);
};
