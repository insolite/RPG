#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Game.h"
#include "MapCell.h"

MapCell::MapCell(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
}

MapCell::~MapCell(void)
{
}

void MapCell::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE MapCell SET name='%s' WHERE id=%d;", name, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
