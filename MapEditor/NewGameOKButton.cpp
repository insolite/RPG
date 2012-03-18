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
	FILE* f;
	std::string query;
	char tmp[1024];
	int i, width, height;

	NewGameWindow* parent = (NewGameWindow*)this->getParent();
	sprintf(path, "game/%s", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	/*
	sprintf(path, "game/%s/data", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/data/location", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	*/
	sprintf(path, "game/%s/resource", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/resource/texture", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);
	sprintf(path, "game/%s/resource/script", parent->gameName->getText().c_str());
	CreateDirectory(path, NULL);

	//Create subdirs

	//Create game db
	sprintf(path, "game/%s/db.sqlite", parent->gameName->getText().c_str());
	sqlite3_open(path, &db);
	//TODO: Init SQL file exec here
	//...
	f = fopen("editor/create_db.sql", "rt");
	query = "";
	while (!feof(f))
	{
		fgets(tmp, 1023, f);
		query += tmp;
	}
	fclose(f);
	sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

	sscanf(parent->mapWidth->getText().c_str(), "%d", &width);
	sscanf(parent->mapWidth->getText().c_str(), "%d", &height);
	char* locationMask = new char[width * height + 1];
	for (i = 0; i < width * height; i++)
	{
		locationMask[i] = '\1';
	}
	locationMask[width * height] = '\0';
	char* sql2 = new char[width * height + 256];
	sprintf(sql2, "INSERT INTO Location VALUES (1, 'start1', %d, %d, '%s');", width, height, locationMask); //CAST(X'%s' AS TEXT))
	sqlite3_exec(db, sql2, NULL, NULL, NULL);
	sqlite3_close(db);
	delete locationMask;
	delete sql2;

	//Add game to list [and select it]
	Universe::instance->gamesListModel->add(parent->gameName->getText());
	Universe::instance->gamesListBox->setSelected(Universe::instance->gamesListModel->getNumberOfElements() - 1);

	parent->setVisible(false);
}
