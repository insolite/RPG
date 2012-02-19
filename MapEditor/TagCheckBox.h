#pragma once

class TagCheckBox :
	public gcn::CheckBox
{
public:
	TagCheckBox(std::string caption, bool selected = false);
	~TagCheckBox(void);
};
