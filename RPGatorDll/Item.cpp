#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Item.h"

Item::Item(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	
}

Item::~Item(void)
{
}
