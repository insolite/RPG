#include "StdAfx.h"
#include "Location.h"


Location::Location(void)
{
}


Location::~Location(void)
{
}

void Location::Print()
{
	for (int i=0; i<height; i++)
	{
		for (int j=0;j<width;j++)
		{
			printf("%3d",(int)mask[i][j]->cellProperty);
		}
		printf("\n");
	}
}

bool Location::Init(char* gameName, int _id)
{
	FILE *f;
	int i, j;
	char path[256];

	id = _id;
	sprintf(path, "game/%s/location/%d/ground.loc", gameName, id);
	f = fopen(path, "rb");
	if (!f)
		return true;
	name = new char[16];
	//fgets(name, 15, f);
	name[0] = fgetc(f);
	for (i = 1; i < 15 && name[i - 1]; i++)
		name[i] = fgetc(f);
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
			//Warning! new MapCell() must be called in resources init. Here must be some kind of concrete cell. Not a cell base
			mask[i][j] = new MapCell();
			mask[i][j]->cellProperty = (CellProperty)fgetc(f);
		}
	}
	fclose(f);
	return false;
}
