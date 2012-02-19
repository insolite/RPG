#pragma once

class LoadGameButton :
	public gcn::Button
{
public:
	bool* continueFlag;

	void mouseClicked(gcn::MouseEvent& mouseEvent);
	
	LoadGameButton(std::string label);
	~LoadGameButton(void);
};
