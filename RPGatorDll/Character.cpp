#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Character.h"

Character::Character(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	
}

Character::~Character(void)
{
}
