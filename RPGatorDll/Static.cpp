#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "SqliteResult.h"
#include "Static.h"

Static::Static(SqliteResult sqliteResult, char* modelPath) : MapObject(sqliteResult, modelPath)
{
	
}

Static::~Static(void)
{
}
