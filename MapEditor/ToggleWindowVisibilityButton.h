#pragma once

class ToggleWindowVisibilityButton :
	public gcn::Button
{
public:
	gcn::Window* window;

	void mouseClicked(gcn::MouseEvent &mouseEvent);

	ToggleWindowVisibilityButton(char* label, gcn::Window* _window);
	~ToggleWindowVisibilityButton(void);
};
