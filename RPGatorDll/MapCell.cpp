#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "MapCell.h"

MapCell::MapCell(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	cellProperty = (CellProperty)sqliteResult.integers["cellProperty"];
}

MapCell::~MapCell(void)
{
}
