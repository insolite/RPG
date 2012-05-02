#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "CurrentGameObject.h"
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
	std::vector<SqliteResult> sqliteResult;
	int rowsCount;

	sqliteResult = SqliteGetRows(Game::instance->db, "SELECT * FROM Location");
	
	locationsCount = 0;
	locations = NULL;
	rowsCount = sqliteResult.size();
	while (locationsCount < rowsCount)
	{
		LocationSpawn(sqliteResult[locationsCount], initializationType);
	}
}

void GameData::LocationSpawn(SqliteResult sqliteResult, InitializationType initializationType)
{
	locationsCount++;
	locations = (Location**)realloc(locations, locationsCount * sizeof(Location*));
	locations[locationsCount - 1] = new Location(sqliteResult, initializationType);
}

void GameData::LocationSpawn(int id, InitializationType initializationType)
{
	char sql[256];
	SqliteResult sqliteResult;

	sprintf(sql, "SELECT * FROM Location WHERE id=%d", id);
	sqliteResult = SqliteGetRows(Game::instance->db, sql)[0];
	LocationSpawn(sqliteResult, initializationType);
}

void GameData::LocationDelete(int index)
{
	//Delete from DB
	char sql[256];
	sprintf(sql, "DELETE FROM Location WHERE id=%d", locations[index]->id);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);

	//Unspawn
	delete locations[index];
	for (int i = index; i < (locationsCount - 1); i++)
		locations[i] = locations[i + 1];
	locationsCount--;
	locations = (Location**)realloc(locations, locationsCount * sizeof(Location*));
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

int GameData::AddLocation(char* name, int width, int height)
{
	char* sql;
	char* locationMask = new char[width * height + 1];
	for (int i = width * height - 1; i >= 0; i--)
	{
		locationMask[i] = '\1';
	}
	locationMask[width * height] = '\0';
	sql = new char[width * height + 256];
	sprintf(sql, "INSERT INTO Location(name, width, height, mask) VALUES ('%s', %d, %d, '%s');", name, width, height, locationMask);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
	delete locationMask;
	delete sql;

	return (int)sqlite3_last_insert_rowid(Game::instance->db);
}

CurrentNPC* GameData::GetNPC( int id )
{
	CurrentNPC* currentNPC;
	for (int i = 0; i < Game::instance->data->locationsCount; i++)
		if (currentNPC = Game::instance->data->locations[i]->GetNPC(id))
			return currentNPC;
	return NULL;
}

CurrentStatic* GameData::GetStatic( int id )
{
	CurrentStatic* currentStatic;
	for (int i = 0; i < Game::instance->data->locationsCount; i++)
		if (currentStatic = Game::instance->data->locations[i]->GetStatic(id))
			return currentStatic;
	return NULL;
}

CurrentItem* GameData::GetItem( int id )
{
	CurrentItem* currentItem;
	for (int i = 0; i < Game::instance->data->locationsCount; i++)
		if (currentItem = Game::instance->data->locations[i]->GetItem(id))
			return currentItem;
	return NULL;
}

CurrentCharacter* GameData::GetCharacter( int id )
{
	CurrentCharacter* currentCharacter;
	for (int i = 0; i < Game::instance->data->locationsCount; i++)
		if (currentCharacter = Game::instance->data->locations[i]->GetCharacter(id))
			return currentCharacter;
	return NULL;
}
