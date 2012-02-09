#pragma once
#include "d:\myfiles\vs2010\projects\rpg\include\guichan\guichan\listmodel.hpp"

class StringListModel :
	public gcn::ListModel
{
public:
	int getNumberOfElements()
	{
		return mStrings.size();
	}

	std::string getElementAt(int i)
	{
		return mStrings.at(i);
	}

	void add(std::string str)
	{
		mStrings.push_back(str);
	}
	
	StringListModel(void);
	~StringListModel(void);

private:
	std::vector<std::string> mStrings;
};

