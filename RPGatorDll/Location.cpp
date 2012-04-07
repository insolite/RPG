#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "NPC.h"
#include "Static.h"
#include "Item.h"
#include "Character.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentNPC.h"
#include "CurrentStatic.h"
#include "CurrentItem.h"
#include "CurrentCharacter.h"
#include "GameResources.h"
#include "GameData.h"
#include "Game.h"
#include "Location.h"

Location::Location(SqliteResult sqliteResult, InitializationType initializationType)
{
	int i, j;

	id = sqliteResult.integers["id"];
	width = sqliteResult.integers["width"];
	height = sqliteResult.integers["height"];
	name = new char[sqliteResult.strings["name"].length() + 1];
	strcpy(name, sqliteResult.strings["name"].c_str());

	mask = new MapCell**[height];
	for (i = 0; i < height; i++)
	{
		mask[i] = new MapCell*[width];
		for (j = 0; j < width; j++)
		{
			//TODO:
			//Warning! getMapCellById instead of fgetc(f) - 1
			mask[i][j] = Game::instance->resources->mapCells[sqliteResult.strings["mask"][height * i + j] - 1];
		}
	}

	if (initializationType == Editor)
	{
		CurrentMapObjectsInit<CurrentNPC>(currentNPCs, currentNPCsCount, "CurrentNPC");
		CurrentMapObjectsInit<CurrentItem>(currentItems, currentItemsCount, "CurrentItem");
		CurrentMapObjectsInit<CurrentStatic>(currentStatics, currentStaticsCount, "CurrentStatic");
		CurrentMapObjectsInit<CurrentCharacter>(currentCharacters, currentCharactersCount, "CurrentCharacter");
	}
	else if (initializationType == Server)
	{
		CurrentMapObjectsInit<CurrentNPC>(currentNPCs, currentNPCsCount, "CurrentNPC");
		CurrentMapObjectsInit<CurrentItem>(currentItems, currentItemsCount, "CurrentItem");
		CurrentMapObjectsInit<CurrentStatic>(currentStatics, currentStaticsCount, "CurrentStatic");
		currentCharacters = NULL; //Online = 0
		currentCharactersCount = 0;
	}
	else //Client
	{
		currentNPCs = NULL;
		currentNPCsCount = 0;
		currentStatics = NULL;
		currentStaticsCount = 0;
		currentItems = NULL;
		currentItemsCount = 0;
		currentCharacters = NULL;
		currentCharactersCount = 0;
	}
}

void Location::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE Location SET name='%s' WHERE id=%d;", name, id);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}

template<class T>
void Location::CurrentMapObjectsInit(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName)
{
	char query[64];
	std::vector<SqliteResult> sqliteResults;
	
	sprintf(query, "SELECT * FROM %s WHERE locationId=%d;", tableName, id); //TODO: Get class T name
	sqliteResults = SqliteGetRows(Game::instance->db, query);
	
	currentMapObjectsCount = 0;
	currentMapObjects = NULL;
	
	int rowsCount = sqliteResults.size();
	while (currentMapObjectsCount < rowsCount)
		SpawnCurrentMapObject<T>(currentMapObjects, currentMapObjectsCount, new T(sqliteResults[currentMapObjectsCount], this));
}

Location::~Location(void)
{
	id = id;
	delete name;
	for (int i = 0; i < height; i++)
		delete[] mask[i];
	//delete[] mask; //TODO: array of array
	//delete mask;
	delete mask;
	//TODO: Delete currentMapObjects
}

void Location::SpawnNPC(CurrentNPC* currentNPC)
{
	SpawnCurrentMapObject<CurrentNPC>(currentNPCs, currentNPCsCount, currentNPC);
}

void Location::SpawnStatic(CurrentStatic* currentStatic)
{
	SpawnCurrentMapObject<CurrentStatic>(currentStatics, currentStaticsCount, currentStatic);
}

void Location::SpawnItem(CurrentItem* currentItem)
{
	SpawnCurrentMapObject<CurrentItem>(currentItems, currentItemsCount, currentItem);
}

void Location::SpawnCharacter(CurrentCharacter* currentCharacter)
{
	SpawnCurrentMapObject<CurrentCharacter>(currentCharacters, currentCharactersCount, currentCharacter);
}

void Location::UnSpawnNPC(CurrentNPC* currentNPC)
{
	UnSpawnCurrentMapObject<CurrentNPC>(currentNPCs, currentNPCsCount, currentNPC);
}

void Location::UnSpawnStatic(CurrentStatic* currentStatic)
{
	UnSpawnCurrentMapObject<CurrentStatic>(currentStatics, currentStaticsCount, currentStatic);
}

void Location::UnSpawnItem(CurrentItem* currentItem)
{
	UnSpawnCurrentMapObject<CurrentItem>(currentItems, currentItemsCount, currentItem);
}

void Location::UnSpawnCharacter(CurrentCharacter* currentCharacter)
{
	UnSpawnCurrentMapObject<CurrentCharacter>(currentCharacters, currentCharactersCount, currentCharacter);
}

void Location::DeleteNPC(CurrentNPC* currentNPC)
{
	DeleteCurrentMapObject<CurrentNPC>(currentNPCs, currentNPCsCount, "CurrentNPC", currentNPC);
}

void Location::DeleteStatic(CurrentStatic* currentStatic)
{
	DeleteCurrentMapObject<CurrentStatic>(currentStatics, currentStaticsCount, "CurrentStatic", currentStatic);
}

void Location::DeleteItem(CurrentItem* currentItem)
{
	DeleteCurrentMapObject<CurrentItem>(currentItems, currentItemsCount, "CurrentItem", currentItem);
}

void Location::DeleteCharacter(CurrentCharacter* currentCharacter)
{
	DeleteCurrentMapObject<CurrentCharacter>(currentCharacters, currentCharactersCount, "CurrentCharacter", currentCharacter);
}

CurrentNPC* Location::GetNPCAt(int x, int y)
{
	return GetCurrentMapObjectAt<CurrentNPC>(currentNPCs, currentNPCsCount, x, y);
}

CurrentStatic* Location::GetStaticAt(int x, int y)
{
	return GetCurrentMapObjectAt<CurrentStatic>(currentStatics, currentStaticsCount, x, y);
}

CurrentItem* Location::GetItemAt(int x, int y)
{
	return GetCurrentMapObjectAt<CurrentItem>(currentItems, currentItemsCount, x, y);
}

CurrentCharacter* Location::GetCharacterAt(int x, int y)
{
	return GetCurrentMapObjectAt<CurrentCharacter>(currentCharacters, currentCharactersCount, x, y);
}

void Location::AddNPC(NPC* base, int x, int y)
{
	char query[256];

	sprintf(query, "INSERT INTO CurrentNPC(baseId, x, y, locationId) VALUES(%d, %d, %d, %d)", base->id, x, y, this->id);
	sqlite3_exec(Game::instance->db, query, NULL, NULL, NULL);
	sprintf(query, "SELECT * FROM CurrentNPC WHERE id=%d", sqlite3_last_insert_rowid(Game::instance->db));
	SqliteResult sqliteResult = SqliteGetRows(Game::instance->db, query)[0];
	SpawnNPC(new CurrentNPC(sqliteResult, this));
}

void Location::AddStatic(Static* base, int x, int y)
{
	char query[256];

	sprintf(query, "INSERT INTO CurrentStatic(baseId, x, y, locationId) VALUES(%d, %d, %d, %d)", base->id, x, y, this->id);
	sqlite3_exec(Game::instance->db, query, NULL, NULL, NULL);
	sprintf(query, "SELECT * FROM CurrentStatic WHERE id=%d", sqlite3_last_insert_rowid(Game::instance->db));
	SqliteResult sqliteResult = SqliteGetRows(Game::instance->db, query)[0];
	SpawnStatic(new CurrentStatic(sqliteResult, this));
}

void Location::AddItem(Item* base, int x, int y)
{
	char query[256];

	sprintf(query, "INSERT INTO CurrentItem(baseId, x, y, locationId, currentCharacterId) VALUES(%d, %d, %d, %d, NULL)", base->id, x, y, this->id);
	sqlite3_exec(Game::instance->db, query, NULL, NULL, NULL);
	sprintf(query, "SELECT * FROM CurrentItem WHERE id=%d", sqlite3_last_insert_rowid(Game::instance->db));
	SqliteResult sqliteResult = SqliteGetRows(Game::instance->db, query)[0];
	SpawnItem(new CurrentItem(sqliteResult, this));
}

void Location::AddCharacter(Character* base, int x, int y, char* login, char* password)
{
	char query[256];

	sprintf(query, "INSERT INTO CurrentCharacter(baseId, x, y, locationId, login, password) VALUES(%d, %d, %d, %d, '%s', '%s')", base->id, x, y, this->id, login, password);
	sqlite3_exec(Game::instance->db, query, NULL, NULL, NULL);
	sprintf(query, "SELECT * FROM CurrentCharacter WHERE id=%d", sqlite3_last_insert_rowid(Game::instance->db));
	SqliteResult sqliteResult = SqliteGetRows(Game::instance->db, query)[0];
	SpawnCharacter(new CurrentCharacter(sqliteResult, this));
}

template<class T>
void Location::SpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject)
{
	currentMapObjectsCount++;
	currentMapObjects = (T**)realloc(currentMapObjects, currentMapObjectsCount * sizeof(T*));
	currentMapObjects[currentMapObjectsCount - 1] = currentMapObject;
}

template<class T>
void Location::UnSpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject)
{
	for (int i = 0; i < currentMapObjectsCount; i++)
	{
		if (currentMapObjects[i] == currentMapObject)
		{
			delete currentMapObject;
			currentMapObjectsCount--;
			if (i != currentMapObjectsCount) //Deleting element is not the last, so we need to 'patch a hole' in array
				currentMapObjects[i] = currentMapObjects[currentMapObjectsCount];
			currentMapObjects = (T**)realloc(currentMapObjects, currentMapObjectsCount * sizeof(T*));
			break;
		}
	}
}

template<class T>
void Location::DeleteCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName, T* currentMapObject)
{
	char query[256];

	sprintf(query, "DELETE FROM %s WHERE id=%d", tableName, currentMapObject->id);
	sqlite3_exec(Game::instance->db, query, NULL, NULL, NULL);
	UnSpawnCurrentMapObject<T>(currentMapObjects, currentMapObjectsCount, currentMapObject);
}

template<class T>
T* Location::GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id)
{
	for (int i = 0; i < currentMapObjectsCount; i++)
		if (currentMapObjects[i]->id == id)
			return currentMapObjects[i];
	return NULL;
}

template<class T>
T* Location::GetCurrentMapObjectAt(T** currentMapObjects, int currentMapObjectsCount, int x, int y)
{
	for (int i = 0; i < currentMapObjectsCount; i++)
		if (currentMapObjects[i]->x == x && currentMapObjects[i]->y == y)
			return currentMapObjects[i];
	return NULL;
}
