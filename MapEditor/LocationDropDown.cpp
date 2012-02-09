#include "StdAfx.h"
#include "LocationDropDown.h"
#include "Universe.h"

LocationDropDown::LocationDropDown(Universe* _universe) : StringDropDown(_universe)
{
}

LocationDropDown::~LocationDropDown(void)
{
}

void LocationDropDown::valueChanged( const gcn::SelectionEvent &event )
{
	universe->SetLocation(universe->locations[this->getSelected()]);
}
