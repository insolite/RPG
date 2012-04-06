#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"

MapObject::MapObject(SqliteResult sqliteResult, char* modelPath) :
	GameObject(sqliteResult)
{
	if (modelPath) //if (Render::instance) //The same
	{ //Client or Editor
		char path[256];
		sprintf(path, "%s/%d.3ds", modelPath, id);
		if (FileExists(path))
			mesh = Render::instance->smgr->getMesh(path);
		else
		{
			sprintf(path, "%s/%d.md2", modelPath, id);
			if (FileExists(path))
				mesh = Render::instance->smgr->getMesh(path);
			else
			{/*
				sprintf(path, "%s/%d.x", modelPath, id);
				if (FileExists(path))
					mesh = Render::instance->smgr->getMesh(path);
				else*/
					mesh = NULL;
			}
		}
		
		sprintf(path, "%s/%d.jpg", modelPath, id);
		if (FileExists(path))
			texture = Render::instance->driver->getTexture(path);
		else
			texture = NULL;
	}
	else
	{ //Server
		mesh = NULL;
		texture = NULL;
	}
}

MapObject::~MapObject(void)
{
	//TODO: delete mesh, texture?
}
