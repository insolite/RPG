#include "StdAfx.h"
#include "GameResources.h"
#include "Universe.h"

GameResources::GameResources(void)
{
	MapCellsInit();
	NpcsInit();
	ItemsInit();
	StaticsInit();
}

GameResources::~GameResources(void)
{
}

bool GameResources::ItemsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/resource/item", Universe::instance->game->name);
	itemsCount = ReadDir(locationsPath, folders, true);
	items = new (Item*[itemsCount]);
	for (i = 0; i < itemsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		items[i] = new Item(id);
	}
	delete[] folders;
	//delete folders;
	return false;
}

bool GameResources::NpcsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/resource/npc", Universe::instance->game->name);
	npcsCount = ReadDir(locationsPath, folders, true);
	npcs = new (NPC*[npcsCount]);
	for (i = 0; i < npcsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		npcs[i] = new NPC(id);
	}
	delete[] folders;
	//delete folders;
	return false;
}

bool GameResources::StaticsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/resource/static", Universe::instance->game->name);
	staticsCount = ReadDir(locationsPath, folders, true);
	statics = new (Static*[staticsCount]);
	for (i = 0; i < staticsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		statics[i] = new Static(id);
	}
	delete[] folders;
	//delete folders;
	return false;
}

bool GameResources::MapCellsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/resource/mapCell", Universe::instance->game->name);
	mapCellsCount = ReadDir(locationsPath, folders, true);
	mapCells = new (MapCell*[mapCellsCount]);
	for (i = 0; i < mapCellsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		mapCells[i] = new MapCell(id);
	}
	delete[] folders;
	//delete folders;
	return false;
}
