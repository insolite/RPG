#include "StdAfx.h"
#include "NewGameWindow.h"

NewGameWindow::NewGameWindow(std::string caption) : Window(caption)
{
	this->setSize(320, 256);
	this->setVisible(false);

	closeButton = new ToggleWindowVisibilityButton("x", this);
	this->add(closeButton);
	closeButton->Dock();

	gameName = new gcn::TextField("game name");
	gameName->setWidth(192);
	//gameName->
	this->add(gameName, 64, 64);

	mapWidth = new gcn::TextField("64");
	mapWidth->setWidth(64);
	this->add(mapWidth, 64, 96);

	mapHeight = new gcn::TextField("64");
	mapHeight->setWidth(64);
	this->add(mapHeight, 144, 96);

	okButton = new NewGameOKButton("OK");
	this->add(okButton, 64, 128);
}

NewGameWindow::~NewGameWindow(void)
{
	delete closeButton;
	delete okButton;
	delete gameName;
	delete mapWidth;
	delete mapHeight;
}
