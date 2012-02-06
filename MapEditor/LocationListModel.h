#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\listmodel.hpp"
#include "Location.h"

class LocationListModel :
	public gcn::ListModel
{
public:
	int locationsCount;
	Location** locations;

    std::string getElementAt(int i)
    {
		char str[16];
		sprintf(str, "%d: %s", locations[i]->id, locations[i]->name);
		return str;
    }

    int getNumberOfElements()
    {
		return locationsCount;
    }

	LocationListModel(Location** _locations, int count);
	~LocationListModel(void);
};
