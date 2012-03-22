#include "StdAfx.h"
#include "Game.h"

Game::Game(char* _name)
{
	char path[279];

	name = _name; //TODO: strcpy?

	sprintf(path, "game/%s/db.sqlite", name);
	if (sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
	//if (sqlite3_open(path, &db) != SQLITE_OK)
	{
		printf("Couldn't load game \"%s\" db\n", name);
		instance = NULL;
		return;
	}

	instance = this;

	resources = new GameResources();
	data = new GameData();
}

Game::~Game(void)
{
	instance = NULL;
	delete resources;
	delete data;
	sqlite3_close(db);
}

Game* Game::instance = NULL;
