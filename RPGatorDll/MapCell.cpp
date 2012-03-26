#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MapObject.h"
#include "SqliteResult.h"
#include "MapCell.h"

MapCell::MapCell(SqliteResult sqliteResult) : MapObject(sqliteResult)
{
	cellProperty = (CellProperty)sqliteResult.integers["cellProperty"];
}

MapCell::~MapCell(void)
{
}
