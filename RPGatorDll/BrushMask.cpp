#include "StdAfx.h"
#include "BrushMask.h"

void BrushMask::Init(int _width, bool** _mask)
{
	int i, j;

	width = _width;
	data = new bool*[width];
	for (i = 0; i < width; i++)
	{
		data[i] = new bool[width];
		for (j = 0; j < width; j++)
			if (_mask)
				data[i][j] = _mask[i][j];
			else
				data[i][j] = true;
	}
}

BrushMask::BrushMask(void)
{
}

BrushMask::~BrushMask(void)
{
	for (int i = 0; i < width; i++)
		delete data[i];
	delete data;
}
