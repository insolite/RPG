#include "StdAfx.h"
#include "BrushListModel.h"

BrushListModel::BrushListModel(CursorBrush** _brushes, int count)
{
	brushes = _brushes;
	brushesCount = count;
}

BrushListModel::~BrushListModel(void)
{
}
