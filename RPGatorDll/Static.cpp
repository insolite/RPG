#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Game.h"
#include "Static.h"

Static::Static(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	
}

Static::~Static(void)
{
}

void Static::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE `Static` SET name='%s' WHERE id=%d;", name, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
