#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MapObject.h"
#include "SqliteResult.h"
#include "Item.h"

Item::Item(SqliteResult sqliteResult) : MapObject(sqliteResult)
{
	
}

Item::~Item(void)
{
}
