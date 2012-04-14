#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "NPC.h"

NPC::NPC(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	sprintf(path, "server/%s/script/skill/%d.lua", Game::instance->name, id);
}

NPC::~NPC(void)
{
}
