#pragma once

class DeleteGameButton :
	public gcn::Button
{
public:
	gcn::ListBox* gamesListBox;

	void mouseClicked(gcn::MouseEvent& mouseEvent);

	DeleteGameButton(std::string label, gcn::ListBox* gamesListBox);
	~DeleteGameButton(void);
};
