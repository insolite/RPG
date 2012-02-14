#pragma once

class ToggleWindowVisibilityButton :
	public gcn::Button
{
public:
	gcn::Window* window;

	void Dock();

	void mouseClicked(gcn::MouseEvent &mouseEvent);

	ToggleWindowVisibilityButton(char* label = "x", gcn::Window* _window = NULL);
	~ToggleWindowVisibilityButton(void);
};
