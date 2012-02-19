#include "StdAfx.h"
#include "Game.h"

Game::Game(char* _name)
{
	name = _name; //TODO: strcpy?
}

Game::~Game(void)
{
	delete resources;
	delete data;
}

void Game::Init()
{
	resources = new GameResources();
	data = new GameData();
}
