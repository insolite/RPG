#pragma once
#include "GameResources.h"
#include "GameData.h"

class Game
{
public:
	char* name;

	static Game* instance;

	GameResources* resources;
	GameData* data;

	__declspec(dllexport) void Init();

	__declspec(dllexport) Game(char* _name);
	__declspec(dllexport) ~Game(void);
};
