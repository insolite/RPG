#pragma once
#include "GameResources.h"
#include "GameData.h"

class Game
{
public:
	char* name;

	GameResources* resources;
	GameData* data;

	void Init();

	Game(char* _name);
	~Game(void);
};
