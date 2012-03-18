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
	for (int i = 0; i < locationsCount; i++)
		delete locations[i];
	delete locations;
}

//Init for MapEditor
void GameData::LocationsInit()
{
	sqlite3_stmt *stmt;
	int result, i, columnsCount;
	std::map<std::string, std::string> strings;
	std::map<std::string, int> integers;
	std::string columnName;

	if (sqlite3_prepare(Game::instance->db, "SELECT * FROM Location;", -1, &stmt, NULL) != SQLITE_OK)
	{
		printf("Couldn't load table from game \"%s\" db\n", Game::instance->name);
		return;
	}
	
	locationsCount = 0;
	locations = NULL;
	
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
						strings[columnName] = (std::string)(char*)sqlite3_column_text(stmt, i);
						break;
					case SQLITE_INTEGER:
						integers[columnName] = sqlite3_column_int(stmt, i);
						break;
				}
			}
			locationsCount++;
			locations = (Location**)realloc(locations, locationsCount * sizeof(Location*));
			locations[locationsCount - 1] = new Location(strings, integers);
		}
		else
		{
			printf("SQLite error. Code: %d\n", result);
		}
	}

	sqlite3_finalize(stmt);
	/*
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
	*/
}

void GameData::MapObjectsInit()
{

}
