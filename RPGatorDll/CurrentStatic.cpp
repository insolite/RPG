#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "Static.h"
#include "CurrentMapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentStatic.h"

//Initialization from DB (Editor, Server)
CurrentStatic::CurrentStatic(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<Static>::CurrentMapObject(sqliteResult, Game::instance->resources->statics, Game::instance->resources->staticsCount, location)
{
}

//Initialization from incoming packet (Client)
CurrentStatic::CurrentStatic(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<Static>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->statics, Game::instance->resources->staticsCount)
{
}

CurrentStatic::~CurrentStatic(void)
{
}
