#pragma once

class QuitButton :
	public gcn::Button
{
public:
	char* continueFlag;

	void mouseClicked(gcn::MouseEvent& mouseEvent);

	QuitButton(std::string label);
	~QuitButton(void);
};
