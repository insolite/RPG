#pragma once

class WindowCloseButton :
	public gcn::Button
{
public:
	void Dock();

	void mouseClicked(gcn::MouseEvent &mouseEvent);

	WindowCloseButton(char* label = "x");
	~WindowCloseButton(void);
};
