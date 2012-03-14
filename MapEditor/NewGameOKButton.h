#pragma once

class NewGameOKButton :
	public gcn::Button
{
public:
	void mouseClicked(gcn::MouseEvent &mouseEvent);

	NewGameOKButton(std::string caption);
	~NewGameOKButton(void);
};
