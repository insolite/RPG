#include "StdAfx.h"
#include "Npc.h"
#include "Universe.h"

NPC::NPC(int _id)
{
	char path[256];
	
	id = _id;
	name = new char[64];
	strcpy(name, "Test name");

	sprintf(path, "game/%s/resource/item/%d/info.dat", Universe::instance->game->name, id);

	FILE* f = fopen(path, "rb");

	if (f != NULL)
	{
		printf("NPC #%d initializtion succeeded \n", id);
		//Operations of gathering info
	}
	fclose(f);
}

NPC::~NPC(void)
{
}
