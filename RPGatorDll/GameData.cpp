#include "StdAfx.h"
#include "GameData.h"
#include "Game.h"

GameData::GameData(void)
{
	LocationsInit();
	MapObjectsInit();
}

GameData::~GameData(void)
{
}

bool GameData::LocationsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/data/location", Game::instance->name);
	locationsCount = ReadDir(locationsPath, folders, false);
	locations = new (Location*[locationsCount]);
	for (i = 0; i < locationsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		locations[i] = new Location(id);
	}
	delete[] folders;
	//delete folders;
	return false;
}

void GameData::MapObjectsInit()
{

}
