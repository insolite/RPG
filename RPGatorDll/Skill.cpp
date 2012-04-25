#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "Skill.h"

Skill::Skill(SqliteResult sqliteResult, char* iconPath) :
	GameObject(sqliteResult, iconPath)
{
	char path[256];

	if (iconPath)
	{
		for (s32 g = 0; g < 7; g++)
		{
			sprintf(path, "client/%s/model/Skill/%d.%d.bmp", Game::instance->name, id, g); //TODO: Editor path
			if (FileExists(path))
				effectTextures.push_back(Render::instance->driver->getTexture(path));
		}
	}
	else
		sprintf(scriptPath, "server/%s/script/Skill/%d.lua", Game::instance->name, id); //TODO: Editor path
}

Skill::~Skill(void)
{
}

void Skill::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE Skill SET name='%s' WHERE id=%d;", name, id);
	//TODO: Tags update //tags='%s', 
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
