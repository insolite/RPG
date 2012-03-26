#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "Item.h"
#include "CurrentMapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentItem.h"

//Initialization from DB (Editor, Server)
CurrentItem::CurrentItem(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<Item>::CurrentMapObject(sqliteResult, Game::instance->resources->items, Game::instance->resources->itemsCount, location)
{
}

//Initialization from incoming packet (Client)
CurrentItem::CurrentItem(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<Item>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->items, Game::instance->resources->itemsCount)
{
}

CurrentItem::~CurrentItem(void)
{
}
