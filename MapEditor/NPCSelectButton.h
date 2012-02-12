#pragma once

class NPCSelectButton :
	public gcn::Button
{
public:
	void mouseClicked(gcn::MouseEvent &mouseEvent);

	NPCSelectButton(char* label);
	~NPCSelectButton(void);
};
