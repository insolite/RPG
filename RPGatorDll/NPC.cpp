#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "NPC.h"

NPC::NPC(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	sprintf(path, "server/%s/script/NPC/%d.lua", Game::instance->name, id);
}

NPC::~NPC(void)
{
}

void NPC::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE NPC SET name='%s', scale=%.0f WHERE id=%d;", name, scale, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
