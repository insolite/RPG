#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "Render.h"
#include "Universe.h"
#include "MenuEventReceiver.h"

bool MenuEventReceiver::OnEvent(const SEvent& event)
{
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
		s32 eventCallerId = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				switch (eventCallerId)
				{
					case LoadGameButton:
					{
						IGUIListBox* lb;
						lb = (IGUIListBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(GamesListBox);
						if (lb->getSelected() >= 0)
						{
							Universe::instance->gameName = new char[256];
							wcstombs(Universe::instance->gameName, lb->getListItem(lb->getSelected()), 255);
							Universe::instance->state = NextLevel;
						}
						break;
					}
					case NewGameButton:
					{
						//IGUIWindow* wnd = (IGUIWindow*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(NewGameWindow);
						IGUIWindow* wnd;
						wnd = Universe::instance->guienv->addWindow(rect< s32 >(278, 208, 522, 392), false, L"New game", 0, NewGameWindow);
						Universe::instance->guienv->addEditBox(L"game name", rect< s32 >(80, 32, 160, 56), true, wnd, GameNameEditBox);
						Universe::instance->guienv->addEditBox(L"64", rect< s32 >(80, 80, 112, 104), true, wnd, DefaultLocationWidthEditBox);
						Universe::instance->guienv->addEditBox(L"64", rect< s32 >(128, 80, 160, 104), true, wnd, DefaultLocationHeightEditBox);
						Universe::instance->guienv->addButton(rect< s32 >(128, 128, 192, 160), wnd, NewGameOKButton, L"OK", L"Create new game");
						break;
					}
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
						IGUIWindow* wnd;
						IGUIEditBox* gneb;

						wnd = (IGUIWindow*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(NewGameWindow);
						gneb = (IGUIEditBox*)wnd->getElementFromId(GameNameEditBox);
						wcstombs(gameName, gneb->getText(), 255);
						sprintf(path, "game/%s", gameName);
						CreateDirectory(path, NULL);
						/*
						sprintf(path, "game/%s/data", gameName);
						CreateDirectory(path, NULL);
						sprintf(path, "game/%s/data/location", gameName);
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
						//TODO: If possible, init SQL file with sqlite library function
						f = fopen("editor/create_db.sql", "rt");
						query = "";
						while (!feof(f))
						{
							fgets(tmp, 1023, f);
							query += tmp;
						}
						fclose(f);
						sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

						swscanf(((IGUIEditBox*)wnd->getElementFromId(DefaultLocationWidthEditBox))->getText(), L"%d", &width);
						swscanf(((IGUIEditBox*)wnd->getElementFromId(DefaultLocationHeightEditBox))->getText(), L"%d", &height);
						
						char* locationMask = new char[width * height + 1];
						for (i = width * height - 1; i >= 0; i--)
						{
							locationMask[i] = '\1';
						}
						locationMask[width * height] = '\0';
						sql = new char[width * height + 256];
						sprintf(sql, "INSERT INTO Location VALUES (1, 'start1', %d, %d, '%s');", width, height, locationMask); //CAST(X'%s' AS TEXT))
						/*
						char* locationMask = new char[2 * width * height + 1];
						for (i = 2 * width * height - 1; i >= 0; i -= 2)
						{
							locationMask[i] = '1';
							locationMask[i - 1] = '0';
						}
						locationMask[2 * width * height] = '\0';
						sql = new char[2 * width * height + 256];
						sprintf(sql, "INSERT INTO Location VALUES (1, 'start1', %d, %d, X'%s');", width, height, locationMask); //CAST(X'%s' AS TEXT))
						*/

						sqlite3_exec(db, sql, NULL, NULL, NULL);
						sqlite3_close(db);
						delete locationMask;
						delete sql;

						//Add this game to the games ListBox and select it
						IGUIListBox* lb = (IGUIListBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(GamesListBox);
						lb->setSelected(lb->addItem(gneb->getText()));
						//TODO: reorder list in alphabetical order
						//Close the NewGameWindow
						wnd->remove();
						break;
					}
					case DeleteGameButton:
					{
						IGUIListBox* lb;
						lb = (IGUIListBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(GamesListBox);
						if (lb->getSelected() >= 0)
						{
							char path[262];
							char str[256];

							wcstombs(str, lb->getListItem(lb->getSelected()), 255);
							sprintf(path, "game/%s", str);
							ClearDir(path);
							RemoveDirectory(path);
							lb->removeItem(lb->getSelected());
						}
						break;
					}
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
