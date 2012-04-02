#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "Render.h"
#include "Universe.h"
#include "EditorEventReceiver.h"

bool EditorEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (KeyIsDown[KEY_ESCAPE])
		{ //Return to the main menu
			delete Universe::instance->gameName;
			Universe::instance->gameName = NULL;
			Universe::instance->state = NextLevel;
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 eventCallerId = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				if (eventCallerId >= MapCellSelectWindowToggleButton && eventCallerId <= CharacterSelectWindowToggleButton)
				{
					if (!Universe::instance->guienv->getRootGUIElement()->getElementFromId(eventCallerId - 10))
					{ //Window is not created
						wchar_t wstr[512]; //Buffer
						MapObject** mapObjects; //General pointer to any MapObjects in GameResources. Is defined in the switch below
						int mapObjectsCount; //'mapObjects' count
						int brushIndex; //Current brush (0: MapCell, 1:NPC, 2:Item, 3:Static, 4:Character)

						brushIndex = eventCallerId - MapCellSelectWindowToggleButton;

						switch (eventCallerId)
						{
							case MapCellSelectWindowToggleButton:
								//Define specific title
								wcscpy(wstr, L"Map cell selection");
								//Define that we would use MapCells as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->mapCells;
								mapObjectsCount = Universe::instance->game->resources->mapCellsCount;
								break;
							case NPCSelectWindowToggleButton:
								//Define specific title
								wcscpy(wstr, L"NPC selection");
								//Define that we would use NPCs as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->npcs;
								mapObjectsCount = Universe::instance->game->resources->npcsCount;
								break;
							case ItemSelectWindowToggleButton:
								//Define specific title
								wcscpy(wstr, L"Item selection");
								//Define that we would use Items as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->items;
								mapObjectsCount = Universe::instance->game->resources->itemsCount;
								break;
							case StaticSelectWindowToggleButton:
								//Define specific title
								wcscpy(wstr, L"Static selection");
								//Define that we would use Statics as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->statics;
								mapObjectsCount = Universe::instance->game->resources->staticsCount;
								break;
							case CharacterSelectWindowToggleButton:
								//Define specific title
								wcscpy(wstr, L"Character selection");
								//Define that we would use Characters as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->characters;
								mapObjectsCount = Universe::instance->game->resources->charactersCount;
								break;
						}

						char** tags;
						int tagsCount;
						IGUIWindow* wnd1;

						//Create window with the specific title 'wstr'
						wnd1 = Universe::instance->guienv->addWindow(rect< s32 >(224, 64, 760, 536), false, wstr, 0, eventCallerId - 10);

						//ListBox for MapObjects
						IGUIListBox* molb = Universe::instance->guienv->addListBox(rect< s32 >(128, 64, 128 + 224, 64 + 320), wnd1, eventCallerId + 5, true);
						for (int i = 0; i < mapObjectsCount; i++)
						{
							swprintf(wstr, L"[%d] ", mapObjects[i]->id);
							mbstowcs(wstr + wcslen(wstr), mapObjects[i]->name, 511);
							molb->addItem(wstr);
							if (Universe::instance->brush[brushIndex] == mapObjects[i])
								molb->setSelected(i); //Select item in list that was used last time in this MapObject list
						}

						tagsCount = Universe::instance->game->resources->GetMapObjectsTags(mapObjects, mapObjectsCount, tags);
						if (tagsCount > 0)
						{ //Tags exists. Therefore we're to put 'All' CheckBox
							Universe::instance->guienv->addCheckBox(true, rect< s32 >(32, 64, 32 + 92, 64 + 16), wnd1, -1, L"All");
							//IGUIElement* container = Universe::instance->guienv->addModalScreen(wnd1);
							//IGUIElement* container = Universe::instance->guienv->addScrollBar(false, rect< s32 >(16, 64, 16 + 92, 64 + 256), wnd1, -1);
							for (int i = 0; i < tagsCount; i++)
							{
								mbstowcs(wstr, tags[i], 511);
								Universe::instance->guienv->addCheckBox(true, rect< s32 >(32, 80 + 16 * i, 32 + 92, 80 + 16 * (i + 1)), wnd1, -1, wstr);
							}
							delete[] tags;
						}

						Universe::instance->guienv->addButton(rect< s32 >(415, 420, 415 + 96, 420 + 32), wnd1, eventCallerId + 10, L"OK", L"Select current map object");
					}
					//Focus just created MapObject selection window (or focus old window)
					Universe::instance->guienv->setFocus(Universe::instance->guienv->getRootGUIElement()->getElementFromId(eventCallerId - 10));
				}
				else if (eventCallerId >= MapCellSelectWindowOKButton && eventCallerId <= CharacterSelectWindowOKButton)
				{
					IGUIListBox* lb = (IGUIListBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(eventCallerId - 20)->getElementFromId(eventCallerId - 5);
					if (lb->getSelected() >= 0)
					{
						int mapObjectId;
						swscanf(lb->getListItem(lb->getSelected()), L"[%d]", &mapObjectId);
						switch (eventCallerId)
						{
							case MapCellSelectWindowOKButton:
								Universe::instance->brush[0] = Universe::instance->game->resources->GetMapCell(mapObjectId);
								break;
							case NPCSelectWindowOKButton:
								Universe::instance->brush[1] = Universe::instance->game->resources->GetNPC(mapObjectId);
								break;
							case ItemSelectWindowOKButton:
								Universe::instance->brush[2] = Universe::instance->game->resources->GetItem(mapObjectId);
								break;
							case StaticSelectWindowOKButton:
								Universe::instance->brush[3] = Universe::instance->game->resources->GetStatic(mapObjectId);
								break;
							case CharacterSelectWindowOKButton:
								Universe::instance->brush[4] = Universe::instance->game->resources->GetCharacter(mapObjectId);
								break;
						}
						//Close parent window (MapObject selection window)
						lb->getParent()->remove();
					}
				}
				else
				{
					switch (eventCallerId)
					{
						case LocationsEditButton:
						{
							IGUIWindow* wnd;
							wnd = (IGUIWindow*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow);
							if (wnd)
							{
								wnd->remove();
								Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->setEnabled(true);
							}
							else
							{
								wnd = Universe::instance->guienv->addWindow(rect< s32 >(Universe::instance->toolbarWidth, 0, Universe::instance->toolbarWidth + 242, 184), false, L"Locations edit", 0, LocationsEditWindow);
								wnd->getCloseButton()->setEnabled(false);
								wnd->getCloseButton()->setVisible(false);
								Universe::instance->guienv->addEditBox(Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->getText(), rect< s32 >(32, 32, 208, 56), true, wnd, LocationNameEditBox);
								Universe::instance->guienv->addEditBox(L"64", rect< s32 >(32, 80, 112, 104), true, wnd, LocationWidthEditBox);
								Universe::instance->guienv->addEditBox(L"64", rect< s32 >(128, 80, 208, 104), true, wnd, LocationHeightEditBox);
								Universe::instance->guienv->addButton(rect< s32 >(32, 128, 32 + 48, 160), wnd, LocationsEditDeleteButton, L"Delete", L"Delete current location");
								Universe::instance->guienv->addButton(rect< s32 >(96, 128, 96 + 48, 160), wnd, LocationsEditSaveButton, L"Save", L"Apply settings to the current location")->setEnabled(false);
								Universe::instance->guienv->addButton(rect< s32 >(160, 128, 160 + 48, 160), wnd, LocationsEditAddButton, L"Save as", L"Apply settings to the new location");
								Universe::instance->guienv->setFocus(wnd);
								Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->setEnabled(false);
							}
							break;
						}
						case LocationsEditSaveButton:
						{
							char str[256];
							int width, height;
							wcstombs(str, Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationNameEditBox)->getText(), 256);
							//swscanf(Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationWidthEditBox)->getText(), L"%d", &width);
							//swscanf(Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationHeightEditBox)->getText(), L"%d", &height);
							delete Universe::instance->currentLocation->name;
							Universe::instance->currentLocation->name = new char[strlen(str) + 1];
							strcpy(Universe::instance->currentLocation->name, str);
							Universe::instance->currentLocation->Update();
							//Update ComboBox
								// ((IGUIComboBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox))->updateItem(L"sd");
							//Close locations edit Window and enable locations ComboBox
							Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->remove();
							Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->setEnabled(true);
							break;
						}
						case LocationsEditAddButton:
						{
							char str[256];
							int width, height;
							wcstombs(str, Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationNameEditBox)->getText(), 255);
							swscanf(Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationWidthEditBox)->getText(), L"%d", &width);
							swscanf(Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationHeightEditBox)->getText(), L"%d", &height);
							//Add location to DB and spawn it
							Universe::instance->game->data->LocationSpawn(Universe::instance->game->data->AddLocation(str, width, height), Editor);
							//Add location to the locations list
							((IGUIComboBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox))->addItem(Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->getElementFromId(LocationNameEditBox)->getText());
							//Close locations edit Window and enable locations ComboBox
							Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->remove();
							Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->setEnabled(true);
							break;
						}
						case LocationsEditDeleteButton:
						{
							IGUIComboBox* lcb = (IGUIComboBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox);
							if (lcb->getItemCount() > 1)
							{ //It's not the last location
								//Delete location from DB and unspawn it
								Universe::instance->game->data->LocationDelete(lcb->getSelected());
								//Delete location from the locations list
								lcb->removeItem(lcb->getSelected());
								//Select another location
								lcb->setSelected(0);
								//Close locations edit Window and enable locations ComboBox
								Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditWindow)->remove();
								Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->setEnabled(true);
							}
							break;
						}
					}
				}
				break;
			case EGET_COMBO_BOX_CHANGED:
				switch (eventCallerId)
				{
					case LocationsComboBox:
						Universe::instance->render->smgr->clear();
						Universe::instance->SetLocation(Universe::instance->game->data->locations[((IGUIComboBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox))->getSelected()]);
						//The code below (3 lines) does not prevent exception during loading another locations due to camera test mode
						ISceneNode* camPos = Universe::instance->render->smgr->addEmptySceneNode();
						camPos->setPosition(vector3df(50,50,10));
						ICameraSceneNode *camera = Universe::instance->render->smgr->addCameraSceneNode(0, vector3df(50,50,10), vector3df(50,0,40));
						Universe::instance->DrawScene();
						break;
				}
				break;
			case EGET_TAB_CHANGED:
				switch (eventCallerId)
				{
					case MapObjectsTabControl:
						Universe::instance->brushIndex = ((IGUITabControl*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(MapObjectsTabControl))->getActiveTab();
						break;
				}
				break;
			case EGET_CHECKBOX_CHANGED:
				/*
				IGUIListBox* molb = Universe::instance->guienv->addListBox(rect< s32 >(128, 64, 128 + 224, 64 + 320), wnd1, eventCallerId + 5, true);
				for (int i = 0; i < mapObjectsCount; i++)
				{
					swprintf(wstr, L"[%d] ", mapObjects[i]->id);
					mbstowcs(wstr + wcslen(wstr), mapObjects[i]->name, 511);
					molb->addItem(wstr);
					if (Universe::instance->brush[brushIndex] == mapObjects[i])
						molb->setSelected(i); //Select item in list that was used last time in this MapObject list
				}
				*/
				//Filter
				//Universe::instance->game->resources->FilterByTag<MapCell>(Universe::instance->game->resources->mapCells, Universe::instance->game->resources->mapCellsCount, , );
				break;
		}
	}

	return false;
}

// метод возвращающий состояние для запрошенной клавиши
bool EditorEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
    
//конструктор, в цикле сбрасываем статус для всех клавиш
EditorEventReceiver::EditorEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}
