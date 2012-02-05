#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\listmodel.hpp"

class FloorListModel :
	public gcn::ListModel
{
public:
	int floorsCount;

    std::string getElementAt(int i)
    {
		if (i)
		{
			char str[8];
			sprintf(str, "%d floor", i);
			return str;
		}
		else
			return "outside";
    }

    int getNumberOfElements()
    {
		return floorsCount;
    }

	FloorListModel(void);
	~FloorListModel(void);
};
