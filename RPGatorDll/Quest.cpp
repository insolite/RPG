#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Quest.h"

Quest::Quest(SqliteResult sqliteResult, char* iconPath) : //iconPath is not used for quests
	GameObject(sqliteResult, NULL)
{
}

Quest::~Quest(void)
{
}
