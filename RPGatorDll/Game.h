#pragma once
#include "GameResources.h"
#include "GameData.h"

class Game
{
public:
	char* name;

	static Game* instance;

	sqlite3* db;
	GameResources* resources;
	GameData* data;

	__declspec(dllexport) Game(char* _name);
	__declspec(dllexport) ~Game(void);
};
