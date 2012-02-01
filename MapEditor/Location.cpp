#include "StdAfx.h"
#include "Location.h"


Location::Location(void)
{
}


Location::~Location(void)
{
}

void Location::Load(char* filename)
{
	FILE *f;
	int i, j;

	f = fopen(filename, "rb");
	width = fgetc(f) * 16 + fgetc(f);
	height = fgetc(f) * 16 + fgetc(f);
	
	mask = new (MapCell*[width]);
	for (i = 0; i < width; i++)
	{
		mask[i] = new (MapCell[height]);
		for (j = 0; j < height; j++)
		{
			mask[i][j].cellProperty = (CellProperty)fgetc(f);
		}
	}
	fclose(f);
}
