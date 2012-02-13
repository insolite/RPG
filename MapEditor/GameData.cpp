#include "StdAfx.h"
#include "GameData.h"
#include "Universe.h"

GameData::GameData(void)
{
	LocationsInit();
}

GameData::~GameData(void)
{
}

bool GameData::LocationsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/location", Universe::instance->game->name);
	locationsCount = ReadDir(locationsPath, folders, true);
	locations = new (Location*[locationsCount]);
	for (i = 0; i < locationsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		locations[i] = new Location(id);
	}
	delete[] folders;
	//delete folders;
	Universe::instance->SetLocation(locations[0]);
	return false;
}
