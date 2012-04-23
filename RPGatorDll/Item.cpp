#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "Item.h"

Item::Item(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	sprintf(path, "server/%s/script/Item/%d.lua", Game::instance->name, id);
}

Item::~Item(void)
{
}

void Item::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE Item SET name='%s' WHERE id=%d;", name, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
