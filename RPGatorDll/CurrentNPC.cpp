#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "NPC.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "Location.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentNPC.h"

//Initialization from DB (Editor, Server)
CurrentNPC::CurrentNPC(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<NPC>::CurrentMapObject(sqliteResult, Game::instance->resources->npcs, Game::instance->resources->npcsCount, location)
{
	if (node)
		setTitle(base->name);
}

//Initialization from incoming packet (Client)
CurrentNPC::CurrentNPC(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<NPC>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->npcs, Game::instance->resources->npcsCount)
{
	if (node)
		setTitle(base->name);
}

CurrentNPC::~CurrentNPC(void)
{
}

void CurrentNPC::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE CurrentNPC SET x=%d, y=%d, locationId=%d WHERE id=%d;", x, y, currentLocation->id, id);
	//sprintf(sql, "UPDATE CurrentCharacter SET HP=%d, MP=%d WHERE id=%d;", HP, MP, id);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
