#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Static.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "Location.h"
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

void CurrentStatic::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE CurrentStatic SET x=%.f, y=%.f, locationId=%d WHERE id=%d;", x, y, currentLocation->id, id);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
