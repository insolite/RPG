#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "Item.h"

Item::Item(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	sprintf(path, "server/%s/script/Item/%d.lua", Game::instance->name, id);
}

Item::~Item(void)
{
}
