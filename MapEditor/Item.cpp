#include "StdAfx.h"
#include "Item.h"
#include "Universe.h"
/*
Item::Item(int _id)
{
	char path[256];

	id = _id;
	name = new char[64];
	strcpy(name, "Test name");

	sprintf(path, "game/%s/resource/item/%d/info.dat", Universe::instance->game->name, id);

	FILE* f = fopen(path, "rb");

	if (f != NULL)
	{
		printf("Item #%d initializtion succeeded \n", id);
		//Operations of gathering info
	}
	fclose(f);
}
*/
Item::Item(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : MapObject(strings, integers)
{
	
}

Item::~Item(void)
{
}
