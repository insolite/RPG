#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "utilities.h"
#include "GameResources.h"
#include "GameData.h"
#include "Game.h"

Game::Game(char* _name, InitializationType initializationType)
{
	char path[279];

	name = new char[strlen(_name) + 1];
	strcpy(name, _name);

	switch (initializationType)
	{
		case Editor:
			sprintf(path, "editor/%s/db.sqlite", name);
			break;
		case Server:
			sprintf(path, "server/%s/db.sqlite", name);
			break;
		case Client:
			sprintf(path, "client/%s/db.sqlite", name);
			break;
	}
	if (sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
	//if (sqlite3_open(path, &db) != SQLITE_OK)
	{
		printf("Couldn't load game \"%s\" db\n", name);
		instance = NULL;
		return;
	}

	instance = this;

	resources = new GameResources();
	data = new GameData(initializationType);
}

Game::~Game(void)
{
	instance = NULL;
	delete resources;
	delete data;
	delete name;
	sqlite3_close(db);
}

Game* Game::instance = NULL;
