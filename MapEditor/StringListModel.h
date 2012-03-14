#pragma once

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
		if (i >= (int)mStrings.size()) //TODO: guichan bug?
			return "*Error*";
		return mStrings.at(i);
	}

	void add(std::string str)
	{
		mStrings.push_back(str);
	}
	
	void remove(int i)
	{
		mStrings.erase(mStrings.begin() + i);
	}

	void clear()
	{
		mStrings.clear();
	}

	StringListModel(void);
	~StringListModel(void);

private:
	std::vector<std::string> mStrings;
};
