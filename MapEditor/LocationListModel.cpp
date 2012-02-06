#include "StdAfx.h"
#include "LocationListModel.h"

LocationListModel::LocationListModel(Location** _locations, int count)
{
	locations = _locations;
	locationsCount = count;
}

LocationListModel::~LocationListModel(void)
{
}
