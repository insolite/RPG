#pragma once
#include "..\include\guichan\guichan.hpp"

class MenuButton :
	public gcn::Button,
	public gcn::MouseListener
{
public:
    void mouseMoved(gcn::MouseEvent &mouseEvent);
    void mouseClicked(gcn::MouseEvent &mouseEvent);

	MenuButton(char* label);
};

