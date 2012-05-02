#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Item.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentCharacter.h"
#include "Location.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentItem.h"

//Initialization from DB (Editor, Server)
CurrentItem::CurrentItem(SqliteResult sqliteResult, Location* location, CurrentCharacter* currentCharacter) :
	CurrentMapObject<Item>::CurrentMapObject(sqliteResult, Game::instance->resources->items, Game::instance->resources->itemsCount, location)
{
	owner = currentCharacter;
	count = sqliteResult.integers["count"];
}

//Initialization from incoming packet (Client)
CurrentItem::CurrentItem(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<Item>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->items, Game::instance->resources->itemsCount)
{
	owner = NULL;
	ScanPacket(currentMapObjectSpawnedPacket, "%i%i%f%f%b%i", NULL, NULL, NULL, NULL, NULL, &count);
}

CurrentItem::~CurrentItem(void)
{
}

void CurrentItem::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE CurrentItem SET x=%.f, y=%.f, locationId=%d, currentCharacterId=%d, count=%d WHERE id=%d;",
		currentLocation ? x : 0,
		currentLocation ? y : 0,
		currentLocation ? currentLocation->id : 0,
		owner ? owner->id : 0,
		count,
		id
		);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
