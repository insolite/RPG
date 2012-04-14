#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "Skill.h"

Skill::Skill(SqliteResult sqliteResult) :
	GameObject(sqliteResult)
{
	sprintf(path, "server/%s/script/skill/%d.lua", Game::instance->name, id);
}

Skill::~Skill(void)
{
}
