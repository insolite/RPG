#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MapObject.h"
#include "SqliteResult.h"
#include "Character.h"

Character::Character(SqliteResult sqliteResult) : MapObject(sqliteResult)
{
	
}

Character::~Character(void)
{
}
