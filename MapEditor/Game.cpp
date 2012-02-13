#include "StdAfx.h"
#include "Game.h"

Game::Game(char* _name)
{
	name = _name;
}

Game::~Game(void)
{
}

void Game::Init()
{
	resources = new GameResources();
	data = new GameData();
}
