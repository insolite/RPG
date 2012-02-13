#include "StdAfx.h"
#include "Location.h"
#include "Universe.h"

Location::Location(int _id)
{
	FILE *f;
	int i, j;
	char path[256];

	id = _id;
	sprintf(path, "game/%s/location/%d/ground.loc", Universe::instance->game->name, id);
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
			//Warning! new MapCell() must be called in resources init. Here must be some kind of concrete cell. Not a cell base
			//mask[i][j] = new MapCell();
			//mask[i][j]->cellProperty = (CellProperty)fgetc(f);

			//TODO:
			//Warning! getMapCellById instead of fgetc(f) - 1
			mask[i][j] = Universe::instance->game->resources->mapCells[fgetc(f) - 1];
		}
	}
	fclose(f);
}

Location::~Location(void)
{
}
