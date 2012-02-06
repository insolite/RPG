#include "StdAfx.h"
#include "CursorBrush.h"

void CursorBrush::Init(int _width, bool** _mask)
{
	int i, j;

	width = _width;
	mask = new bool*[width];
	for (i = 0; i < width; i++)
	{
		mask[i] = new bool[width];
		for (j = 0; j < width; j++)
			if (_mask)
				mask[i][j] = _mask[i][j];
			else
				mask[i][j] = false;
	}
}

CursorBrush::CursorBrush(void)
{
}

CursorBrush::~CursorBrush(void)
{
	for (int i = 0; i < width; i++)
		delete mask[i];
	delete mask;
}
