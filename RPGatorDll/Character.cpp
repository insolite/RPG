#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Game.h"
#include "Character.h"

Character::Character(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	speed = sqliteResult.doubles["speed"];
}

Character::~Character(void)
{
}

void Character::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE `Character` SET name='%s', scale=%.0f WHERE id=%d;", name, scale, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
