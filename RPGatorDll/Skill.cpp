#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Skill.h"

Skill::Skill(SqliteResult sqliteResult) :
	GameObject(sqliteResult)
{
}

Skill::~Skill(void)
{
}
