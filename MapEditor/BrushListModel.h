#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\listmodel.hpp"
#include "CursorBrush.h"

class BrushListModel :
	public gcn::ListModel
{
public:
	int brushesCount;
	CursorBrush** brushes;

    std::string getElementAt(int i)
    {
		char str[16];
		sprintf(str, "%dx", brushes[i]->width);
		return str;
    }

    int getNumberOfElements()
    {
		return brushesCount;
    }

	BrushListModel(CursorBrush** _brushes, int count);
	~BrushListModel(void);
};

