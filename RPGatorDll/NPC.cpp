#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "NPC.h"

NPC::NPC(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
}

NPC::~NPC(void)
{
}
