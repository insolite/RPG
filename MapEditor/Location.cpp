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
			printf("%3d",(int)mask[i][j].cellProperty);
		}
		printf("\n");
	}
}

void Location::Load(char* filename)
{
	FILE *f;
	int i, j;

	f = fopen(filename, "rb");
	width = fgetc(f) * 16 + fgetc(f);
	height = fgetc(f) * 16 + fgetc(f);
	
	mask = new (MapCell*[width]);
	for (i = 0; i < height; i++)
	{
		mask[i] = new (MapCell[height]);
		for (j = 0; j < width; j++)
		{
			mask[i][j].cellProperty = (CellProperty)fgetc(f);
		}
	}
	fclose(f);
}
