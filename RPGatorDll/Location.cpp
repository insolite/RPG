#include "StdAfx.h"
#include "Location.h"
#include "Game.h"
/*
Location::Location(int _id)
{
	FILE *f;
	int i, j;
	char path[256];

	id = _id;
	sprintf(path, "game/%s/data/location/%d.loc", Game::instance->name, id);
	f = fopen(path, "rb");
	if (!f)
		return;
	name = new char[16];
	//fgets(name, 15, f);
	name[0] = fgetc(f);
	for (i = 1; i < 15 && name[i - 1]; i++)
		name[i] = fgetc(f);
	//TODO: binary reader
	width = fgetc(f) * 16;
	width += fgetc(f);
	height = fgetc(f) * 16;
	height += fgetc(f);
	
	mask = new MapCell**[height];
	for (i = 0; i < height; i++)
	{
		mask[i] = new MapCell*[width];
		for (j = 0; j < width; j++)
		{
			//TODO:
			//Warning! getMapCellById instead of fgetc(f) - 1
			mask[i][j] = Game::instance->resources->mapCells[fgetc(f) - 1];
		}
	}
	fclose(f);
}
*/

Location::Location(std::map<std::string, std::string> strings, std::map<std::string, int> integers)
{
	int i, j;

	id = integers["id"];
	width = integers["width"];
	height = integers["height"];
	name = new char[strings["name"].length() + 1];
	strcpy(name, strings["name"].c_str());

	mask = new MapCell**[height];
	for (i = 0; i < height; i++)
	{
		mask[i] = new MapCell*[width];
		for (j = 0; j < width; j++)
		{
			//TODO:
			//Warning! getMapCellById instead of fgetc(f) - 1
			mask[i][j] = Game::instance->resources->mapCells[strings["mask"][height * i + j] - 1];
		}
	}

	currentCharacters = NULL;
	currentCharactersCount = 0;
}

Location::~Location(void)
{
	delete name;
	for (int i = 0; i < height; i++)
		delete[] mask[i];
	//delete[] mask; //TODO: array of array
	//delete mask;
	delete mask;
}

void Location::AddNPC(CurrentNPC* currentNPC)
{
	//Adds NPC to array currentNPCs
	//Adds record to GameData db (Universe::instance->game->data->db)
}

bool Location::AddCurrentCharacter(CurrentCharacter* currentCharacter)
{
	currentCharactersCount++;
	currentCharacters = (CurrentCharacter**)realloc(currentCharacters, currentCharactersCount * sizeof(CurrentCharacter));
	currentCharacters[currentCharactersCount - 1] = currentCharacter;

	return false;
}
