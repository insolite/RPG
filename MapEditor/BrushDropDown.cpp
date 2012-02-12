#include "StdAfx.h"
#include "BrushDropDown.h"

BrushDropDown::BrushDropDown(Universe* _universe) : StringDropDown(_universe)
{
}

BrushDropDown::~BrushDropDown(void)
{
}

void BrushDropDown::valueChanged( const gcn::SelectionEvent &event )
{
	universe->currentBrushMask = universe->brushMasks[this->getSelected()];
}
