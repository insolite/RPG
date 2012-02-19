#include "StdAfx.h"
#include "GameResources.h"
#include "Universe.h"

GameResources::GameResources(void)
{
	char path[279];

	sprintf(path, "game/%s/resources.sqlite", Universe::instance->game->name);
	if (sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
	//if (sqlite3_open(path, &db) != SQLITE_OK)
	{
		printf("Couldn't load game \"%s\" resources", Universe::instance->game->name);
		return;
	}

	MapObjectsInit<MapCell>(mapCells, mapCellsCount, "MapCell");
	MapObjectsInit<NPC>(npcs, npcsCount, "NPC");
	MapObjectsInit<Item>(items, itemsCount, "Item");
	MapObjectsInit<Static>(statics, staticsCount, "StaticObject");

	/*
	MapCellsInit();
	NpcsInit();
	ItemsInit();
	StaticsInit();
	*/
}

GameResources::~GameResources(void)
{
	delete[] mapCells;
	delete[] npcs;
	delete[] items;
	delete[] statics;
	sqlite3_close(db);
}

template<class T>
void GameResources::MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName)
{
	char query[64];
	sqlite3_stmt *stmt;
	int result, i, columnsCount;
	std::map<std::string, std::string> strings;
	std::map<std::string, int> integers;
	std::string columnName;
	
	sprintf(query, "SELECT * FROM %s;", tableName); //TODO: Get class T name
	if (sqlite3_prepare(db, query, -1, &stmt, NULL) != SQLITE_OK)
	{
		printf("Couldn't load table from game \"%s\" resources", Universe::instance->game->name);
		return;
	}
	
	mapObjectsCount = 0;
	mapObjects = NULL;
	
	while ((result = sqlite3_step(stmt)) != SQLITE_DONE)
	{
		if (result == SQLITE_ROW)
		{
			columnsCount = sqlite3_column_count(stmt);
			for (i = 0; i < columnsCount; i++)
			{
				columnName = sqlite3_column_name(stmt, i);
				switch (sqlite3_column_type(stmt, i))
				{
					case SQLITE_TEXT:
						strings[columnName] = (string)(char*)sqlite3_column_text(stmt, i);
						break;
					case SQLITE_INTEGER:
						integers[columnName] = sqlite3_column_int(stmt, i);
						break;
				}
			}
			mapObjectsCount++;
			mapObjects = (T**)realloc(mapObjects, mapObjectsCount * sizeof(T*));
			mapObjects[mapObjectsCount - 1] = new T(strings, integers);
		}
		else
		{
			printf("SQLite error. Code: %d\n", result);
		}
	}
	strings.clear();
	integers.clear();
	sqlite3_finalize(stmt);
}
/*
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
*/
