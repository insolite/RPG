#include "StdAfx.h"
#include "CursorBrush.h"

CursorBrush::CursorBrush(int id)
{
	char path[64];
	int i, j;
	FILE* f;

	sprintf(path, "editor/brush/%d.dat", id);
	f = fopen(path, "rb");
	width = fgetc(f);
	mask = new bool*[width];
	for (i = 0; i < width; i++)
	{
		mask[i] = new bool[width];
		for (j = 0; j < width; j++)
			mask[i][j] = fgetc(f);
	}
	fclose(f);
}

CursorBrush::~CursorBrush(void)
{
	for (int i = 0; i < width; i++)
		delete mask[i];
	delete mask;
}
