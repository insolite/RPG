#include "StdAfx.h"
#include "Game.h"

Game::Game(char* _name)
{
	name = _name; //TODO: strcpy?
	instance = this;
}

Game::~Game(void)
{
	delete resources;
	delete data;
	instance = NULL;
}

void Game::Init()
{
	resources = new GameResources();
	data = new GameData();
}

Game* Game::instance = NULL;
