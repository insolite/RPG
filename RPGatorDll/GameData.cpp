#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "CurrentMapObject.h"
#include "CurrentNPC.h"
#include "CurrentStatic.h"
#include "CurrentItem.h"
#include "CurrentCharacter.h"
#include "Location.h"
#include "Game.h"
#include "GameData.h"

GameData::GameData(InitializationType initializationType)
{
	LocationsInit(initializationType);
}

GameData::~GameData(void)
{
	for (int i = 0; i < locationsCount; i++)
		delete locations[i];
	delete locations;
}

void GameData::LocationsInit(InitializationType initializationType)
{
	int rowsCount;
	std::vector<SqliteResult> sqliteResult;

	sqliteResult = SqliteGetRows(Game::instance->db, "SELECT * FROM Location");
	
	locationsCount = 0;
	locations = NULL;
	
	while (locationsCount < sqliteResult.size())
	{
		locationsCount++;
		locations = (Location**)realloc(locations, locationsCount * sizeof(Location*));
		locations[locationsCount - 1] = new Location(sqliteResult[locationsCount - 1], initializationType);
	}
}

Location* GameData::GetLocation(int id)
{
	for (int i = 0; i < locationsCount; i++)
	{
		if (locations[i]->id == id)
			return locations[i];
	}
	return NULL;
}
