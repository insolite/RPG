#include "StdAfx.h"
#include "MapCell.h"
#include "Universe.h"
/*
MapCell::MapCell(int _id)
{
	char path[256];
	FILE* f;
	int a;

	id = _id;
	name = new char[64];
	strcpy(name, "Test name");

	sprintf(path, "game/%s/resource/mapCell/%d/info.dat", Universe::instance->game->name, id);

	f = fopen(path, "rb");
	if (!f)
		return;
	printf("MapCell #%d initializtion succeeded \n", id);
	fgetc(f); //id
	fgetc(f); //id
	cellProperty = (CellProperty)fgetc(f);
	fclose(f);
}
*/
MapCell::MapCell(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : MapObject(strings, integers)
{
	cellProperty = (CellProperty)integers["cellProperty"];
}

MapCell::~MapCell(void)
{
}
