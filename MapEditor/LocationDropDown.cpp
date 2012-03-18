#include "StdAfx.h"
#include "LocationDropDown.h"
#include "Universe.h"

LocationDropDown::LocationDropDown(void) : StringDropDown()
{
}

LocationDropDown::~LocationDropDown(void)
{
}

void LocationDropDown::valueChanged( const gcn::SelectionEvent &event )
{
	Universe::instance->SetLocation(Universe::instance->game->data->locations[this->getSelected()]);
}
