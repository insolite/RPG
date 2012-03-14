#pragma once

class TagCheckBox :
	public gcn::CheckBox
{
public:
	void mouseClicked(gcn::MouseEvent& mouseEvent);

	TagCheckBox(std::string caption, bool selected = false);
	~TagCheckBox(void);
};
