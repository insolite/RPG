#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\listmodel.hpp"
#include "NPC.h"

class NPCListModel :
	public gcn::ListModel
{
public:
	NPC** npcs;
	int npcsCount;

    std::string getElementAt(int i)
    {
		char* t[] = {"1", "2", "3"};
		return t[i];
		//return npcs[i]->name;
    }

    int getNumberOfElements()
    {
		return 3;
        //return npcsCount;
    }

	NPCListModel(void);
	~NPCListModel(void);
};

