#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "MapObject.h"
#include "Quest.h"

Quest::Quest(SqliteResult sqliteResult) : MapObject(sqliteResult)
{
}

Quest::~Quest(void)
{
}
