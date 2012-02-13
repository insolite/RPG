#include "StdAfx.h"
#include "Static.h"
#include "Universe.h"

Static::Static(int _id)
{
	mask = new BrushMask();
	mask->Init(3);

	char path[256];
	
	id = _id;
	name = new char[64];
	strcpy(name, "Test name");

	sprintf(path, "game/%s/resource/static/%d/info.dat", Universe::instance->game->name, id);

	FILE* f = fopen(path, "rb");

	if (f != NULL)
	{
		printf("Static #%d initializtion succeeded \n", id);
		//Operations of gathering info
	}
	fclose(f);
}

Static::~Static(void)
{
}
