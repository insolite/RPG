#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Game.h"
#include "Quest.h"

Quest::Quest(SqliteResult sqliteResult, char* iconPath) : //iconPath is not used for quests
	GameObject(sqliteResult, NULL)
{
}

Quest::~Quest(void)
{
}

void Quest::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE Quest SET name='%s' WHERE id=%d;", name, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
