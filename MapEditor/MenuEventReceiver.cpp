#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "Render.h"
#include "Universe.h"
#include "MenuEventReceiver.h"

// наш собственный обработчик событий
bool MenuEventReceiver::OnEvent(const SEvent& event)
{
	// просто запоминаем состояние любой клавиши - нажата/отжата
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (KeyIsDown[KEY_ESCAPE])
		{
			Universe::instance->render->device->closeDevice();
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID(); // получаем идентификатор элемента, вызвавшего событие

		switch(event.GUIEvent.EventType) // обрабатываем события относительно типа
		{
			case EGET_BUTTON_CLICKED:
				switch (id)
				{
					case LoadGameButton:
						if (Universe::instance->lb->getSelected() >= 0)
						{
							Universe::instance->gameName = new char[256];
							wcstombs(Universe::instance->gameName, Universe::instance->lb->getListItem(Universe::instance->lb->getSelected()), 255);
							Universe::instance->state = NextLevel;
						}
						break;
					case NewGameButton:
						Universe::instance->newGameWindow = Universe::instance->menuGuienv->addWindow(rect< s32 >(278, 208, 522, 392), false, L"New game", 0, NewGameWindow);
						Universe::instance->gameNameEditBox = Universe::instance->menuGuienv->addEditBox(L"game name", rect< s32 >(80, 32, 160, 56), true, Universe::instance->newGameWindow, GameNameEditBox);
						Universe::instance->defaultLocationWidthEditBox = Universe::instance->menuGuienv->addEditBox(L"64", rect< s32 >(80, 80, 112, 104), true, Universe::instance->newGameWindow, DefaultLocationWidthEditBox);
						Universe::instance->defaultLocationHeightEditBox = Universe::instance->menuGuienv->addEditBox(L"64", rect< s32 >(128, 80, 160, 104), true, Universe::instance->newGameWindow, DefaultLocationHeightEditBox);
						Universe::instance->menuGuienv->addButton(rect< s32 >(128, 128, 192, 160), Universe::instance->newGameWindow, NewGameOKButton, L"OK", L"Create new game");
						break;
					case NewGameOKButton:
						{
						char path[262 + 64];
						char gameName[256];
						char* sql;
						sqlite3* db;
						FILE* f;
						std::string query;
						char tmp[1024];
						int i, width, height;

						//Universe::instance->gameNameEditBox->getText();
						wcstombs(gameName, Universe::instance->gameNameEditBox->getText(), 255);
						sprintf(path, "game/%s", gameName);
						CreateDirectory(path, NULL);
						/*
						sprintf(path, "game/%s/data", parent->gameName->getText().c_str());
						CreateDirectory(path, NULL);
						sprintf(path, "game/%s/data/location", parent->gameName->getText().c_str());
						CreateDirectory(path, NULL);
						*/
						sprintf(path, "game/%s/resource", gameName);
						CreateDirectory(path, NULL);
						sprintf(path, "game/%s/resource/texture", gameName);
						CreateDirectory(path, NULL);
						sprintf(path, "game/%s/resource/script", gameName);
						CreateDirectory(path, NULL);

						//Create subdirs

						//Create game db
						sprintf(path, "game/%s/db.sqlite", gameName);
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

						//sscanf(parent->mapWidth->getText().c_str(), "%d", &width);
						//sscanf(parent->mapWidth->getText().c_str(), "%d", &height);
						width = WCharToInt(Universe::instance->defaultLocationWidthEditBox->getText());
						height = WCharToInt(Universe::instance->defaultLocationHeightEditBox->getText());
						char* locationMask = new char[width * height + 1];
						for (i = 0; i < width * height; i++)
						{
							locationMask[i] = '\1';
						}
						locationMask[width * height] = '\0';
						sql = new char[width * height + 256];
						sprintf(sql, "INSERT INTO Location VALUES (1, 'start1', %d, %d, '%s');", width, height, locationMask); //CAST(X'%s' AS TEXT))
						sqlite3_exec(db, sql, NULL, NULL, NULL);
						sqlite3_close(db);
						delete locationMask;
						delete sql;

						Universe::instance->lb->addItem(Universe::instance->gameNameEditBox->getText());
						//Universe::instance->newGameWindow->drop();
						}
						break;
					case DeleteGameButton:
						if (Universe::instance->lb->getSelected() >= 0)
						{
							char path[262];
							char str[256];

							wcstombs(str, Universe::instance->lb->getListItem(Universe::instance->lb->getSelected()), 255);
							sprintf(path, "game/%s", str);
							ClearDir(path);
							RemoveDirectory(path);
							Universe::instance->lb->removeItem(Universe::instance->lb->getSelected());
						}
						break;
					case QuitMenuButton:
						Universe::instance->state = Exit;
						break;
				}
				break;
		}
	}

	return false;
}

// метод возвращающий состояние для запрошенной клавиши
bool MenuEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

//конструктор, в цикле сбрасываем статус для всех клавиш
MenuEventReceiver::MenuEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}
