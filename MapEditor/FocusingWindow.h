#pragma once

class FocusingWindow :
	public gcn::Window
{
public:
	void mouseEntered(gcn::MouseEvent &mouseEvent);

	FocusingWindow(std::string caption);
	~FocusingWindow(void);
};
