#include "StdAfx.h"
#include "NewGameOKButton.h"
#include "NewGameWindow.h"
#include "Universe.h"

NewGameOKButton::NewGameOKButton(std::string caption) : Button(caption)
{
}

NewGameOKButton::~NewGameOKButton(void)
{
}

void NewGameOKButton::mouseClicked(gcn::MouseEvent &mouseEvent)
{
	char path[262 + 64];
	char sql[256];
	sqlite3* db;

	NewGameWindow* parent = (NewGameWindow*)this->getParent();
	sprintf(path, "game/%s", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/data", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/data/location", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/resource", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/resource/texture", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/resource/script", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);

	//Create subdirs

	//Create resources db
	sprintf(path, "game/%s/resources.sqlite", parent->gameName->getText().c_str());
	sqlite3_open(path, &db);
	//TODO: Init SQL file exec here
	//...
	sprintf(sql, "INSERT INTO config VALUES ('gameName', '%s');", parent->gameName->getText().c_str());
	sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_close(db);

	//Create data db
	sprintf(path, "game/%s/data.sqlite", parent->gameName->getText().c_str());
	sqlite3_open(path, &db);
	//TODO: Init SQL file exec here
	//...
	//sprintf(sql, "INSERT INTO location VALUES ('gameName', '%s');", parent->gameName->getText().c_str());
	//sqlite3_exec(db, sql, NULL, NULL, NULL);
	sqlite3_close(db);

	//Add game to list [and select it]
	Universe::instance->gamesListModel->add(parent->gameName->getText());
	Universe::instance->gamesListBox->setSelected(Universe::instance->gamesListModel->getNumberOfElements() - 1);

	parent->setVisible(false);
}
