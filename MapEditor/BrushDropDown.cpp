#include "StdAfx.h"
#include "BrushDropDown.h"

BrushDropDown::BrushDropDown(void) : StringDropDown()
{
}

BrushDropDown::~BrushDropDown(void)
{
}

void BrushDropDown::valueChanged( const gcn::SelectionEvent &event )
{
	Universe::instance->currentBrushMask = Universe::instance->brushMasks[this->getSelected()];
}
