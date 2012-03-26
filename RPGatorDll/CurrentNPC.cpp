#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "NPC.h"
#include "CurrentMapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentNPC.h"

//Initialization from DB (Editor, Server)
CurrentNPC::CurrentNPC(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<NPC>::CurrentMapObject(sqliteResult, Game::instance->resources->npcs, Game::instance->resources->npcsCount, location)
{
}

//Initialization from incoming packet (Client)
CurrentNPC::CurrentNPC(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<NPC>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->npcs, Game::instance->resources->npcsCount)
{
}

CurrentNPC::~CurrentNPC(void)
{
}
