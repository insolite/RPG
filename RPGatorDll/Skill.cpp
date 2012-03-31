#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "MapObject.h"
#include "Skill.h"

Skill::Skill(SqliteResult sqliteResult) : MapObject(sqliteResult)
{
}

Skill::~Skill(void)
{
}
