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

template<class T>
void Location::CurrentMapObjectsInit(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName)
{
	char query[64];
	std::vector<SqliteResult> sqliteResults;
	
	sprintf(query, "SELECT * FROM %s WHERE locationId=%d;", tableName, id); //TODO: Get class T name
	sqliteResults = SqliteGetRows(Game::instance->db, query);
	
	currentMapObjectsCount = 0;
	currentMapObjects = NULL;
	
	while (currentMapObjectsCount < sqliteResults.size())
	{
		currentMapObjectsCount++;
		currentMapObjects = (T**)realloc(currentMapObjects, currentMapObjectsCount * sizeof(T*));
		currentMapObjects[currentMapObjectsCount - 1] = new T(sqliteResults[currentMapObjectsCount - 1], this);
	}
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

void Location::AddNPC(CurrentNPC* currentNPC)
{
	//Adds NPC to array currentNPCs
	//Adds record to GameData db (Universe::instance->game->data->db)
}

void Location::AddCurrentCharacter(CurrentCharacter* currentCharacter)
{
	currentCharactersCount++;
	currentCharacters = (CurrentCharacter**)realloc(currentCharacters, currentCharactersCount * sizeof(CurrentCharacter));
	currentCharacters[currentCharactersCount - 1] = currentCharacter;
}

template<class T>
T* Location::GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id)
{
	for (int i = 0; i < currentCharactersCount; i++)
		if (currentMapObjects[i]->id == id)
			return currentMapObjects[i];
	return NULL;
}
