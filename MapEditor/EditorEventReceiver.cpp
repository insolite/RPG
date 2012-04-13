#include "StdAfx.h"
#include "ForwardDeclaration.h"
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
		/*
		else if (KeyIsDown[KEY_LEFT] || KeyIsDown[KEY_RIGHT] || KeyIsDown[KEY_UP] || KeyIsDown[KEY_DOWN])
		{
			core::vector3df Km = Universe::instance->camPos->getPosition();
			Universe::instance->render->Kt = Universe::instance->camera->getTarget();
			
			if (KeyIsDown[KEY_LEFT])
			{
				Universe::instance->render->Kt.X -= CAMERA_STEP;
				Km.X -= CAMERA_STEP;
				Universe::instance->camPos->setPosition(Km);
			}
			if (KeyIsDown[KEY_RIGHT])
			{
				Universe::instance->render->Kt.X += CAMERA_STEP;
				Km.X += CAMERA_STEP;
				Universe::instance->camPos->setPosition(Km);
			}
			if (KeyIsDown[KEY_UP])
			{
				Universe::instance->render->Kt.Z += CAMERA_STEP;
				Km.Z += CAMERA_STEP;
				Universe::instance->camPos->setPosition(Km);
			}
			if (KeyIsDown[KEY_DOWN])
			{
				Universe::instance->render->Kt.Z -= CAMERA_STEP;
				Km.Z -= CAMERA_STEP;
				Universe::instance->camPos->setPosition(Km);
			}
			Universe::instance->camera->setPosition(Km);
			Universe::instance->camera->setTarget(Universe::instance->render->Kt);
		}
		*/
	}
	else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		for (s32 i = 0; i < EMIE_COUNT; ++i)
            Mouse[i] = i == event.MouseInput.Event;
		IGUIElement* guiElement = Universe::instance->guienv->getRootGUIElement()->getElementFromPoint(vector2di(event.MouseInput.X, event.MouseInput.Y));
		if (guiElement != NULL)
		{ //Mouse is in a window area
			if (guiElement->getID() != 0) //Mouse is on GUI element
				return false;
		}
		else //Mouse is not in a window area
			return false;
		vector3df position = Universe::instance->render->MouseCoordToWorldCoord();
		int x, y;
		x = position.X / CELL_SIZE;
		y = position.Z / CELL_SIZE;
		if (Mouse[EMIE_LMOUSE_PRESSED_DOWN])
		{ //Add CurrentMapObject
			//Add from brush
			switch (Universe::instance->brushIndex)
			{
				case 0: //MapCell
					Universe::instance->currentLocation->mask[y][x] = (MapCell*)Universe::instance->brush[0];
					//TODO: Save location before exit
					break;
				case 1: //NPC
					Universe::instance->currentLocation->AddNPC((NPC*)Universe::instance->brush[1], x, y);
					break;
				case 2: //Static
					Universe::instance->currentLocation->AddStatic((Static*)Universe::instance->brush[2], x, y);
					break;
				case 3: //Item
					Universe::instance->currentLocation->AddItem((Item*)Universe::instance->brush[3], x, y);
					break;
				case 4: //Character
					Universe::instance->currentLocation->AddCharacter((Character*)Universe::instance->brush[4], x, y, "default_login", "default_password");
					break;
			}
		}
		else if (Mouse[EMIE_RMOUSE_PRESSED_DOWN])
		{ //Delete CurrentMapObject
			CurrentMapObject<MapObject>* deletingCurrentMapObject;
			if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->getNodeUnderCursor<CurrentNPC>(Universe::instance->currentLocation->currentNPCs, Universe::instance->currentLocation->currentNPCsCount))
				Universe::instance->currentLocation->DeleteNPC((CurrentNPC*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->getNodeUnderCursor<CurrentStatic>(Universe::instance->currentLocation->currentStatics, Universe::instance->currentLocation->currentStaticsCount))
				Universe::instance->currentLocation->DeleteStatic((CurrentStatic*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->getNodeUnderCursor<CurrentItem>(Universe::instance->currentLocation->currentItems, Universe::instance->currentLocation->currentItemsCount))
				Universe::instance->currentLocation->DeleteItem((CurrentItem*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->getNodeUnderCursor<CurrentCharacter>(Universe::instance->currentLocation->currentCharacters, Universe::instance->currentLocation->currentCharactersCount))
				Universe::instance->currentLocation->DeleteCharacter((CurrentCharacter*)deletingCurrentMapObject);
			/* //Selection by cell
			CurrentMapObject<MapObject>* deletingCurrentMapObject;
			if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->currentLocation->GetNPCAt(x, y))
				Universe::instance->currentLocation->DeleteNPC((CurrentNPC*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->currentLocation->GetStaticAt(x, y))
				Universe::instance->currentLocation->DeleteStatic((CurrentStatic*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->currentLocation->GetItemAt(x, y))
				Universe::instance->currentLocation->DeleteItem((CurrentItem*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->currentLocation->GetCharacterAt(x, y))
				Universe::instance->currentLocation->DeleteCharacter((CurrentCharacter*)deletingCurrentMapObject);
			*/
		}
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 eventCallerId = event.GUIEvent.Caller->getID();
		IGUIElement* eventCaller = event.GUIEvent.Caller;

		switch(event.GUIEvent.EventType)
		{
			case EGET_LISTBOX_CHANGED:
				switch (eventCallerId)
				{
					case MapObjectSelectWindowListBox:
						int selectedMapObjectId;
						MapObject* selectedMapObject;
						int index = eventCaller->getParent()->getID() - MapCellSelectWindow; //Parent window index
						CGUIMeshViewer* mv = (CGUIMeshViewer*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapObjectMeshViever, true);
						IGUIListBox* lb = (IGUIListBox*)eventCaller;
						swscanf(lb->getListItem(lb->getSelected()), L"[%d]", &selectedMapObjectId);
						switch (index)
						{
							case 0:
								selectedMapObject = Universe::instance->game->resources->GetMapCell(selectedMapObjectId);
								break;
							case 1:
								selectedMapObject = Universe::instance->game->resources->GetNPC(selectedMapObjectId);
								break;
							case 2:
								selectedMapObject = Universe::instance->game->resources->GetStatic(selectedMapObjectId);
								break;
							case 3:
								selectedMapObject = Universe::instance->game->resources->GetItem(selectedMapObjectId);
								break;
							case 4:
								selectedMapObject = Universe::instance->game->resources->GetCharacter(selectedMapObjectId);
								break;
						}
						SMaterial* sm = new SMaterial();
						sm->setTexture(0, selectedMapObject->texture);
						sm->setFlag(EMF_LIGHTING, false);
						mv->setMesh(selectedMapObject->mesh);
						mv->setMaterial(*sm);
						break;
				}
				break;
			case EGDT_WINDOW_CLOSE:
				if (eventCallerId >= MapCellSelectWindow && eventCallerId <= CharacterSelectWindow)
				{
					Universe::instance->render->smgr->setActiveCamera(Universe::instance->camera);
				}
				break;
			/*
			case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
			{
				switch (eventCallerId)
				{
					case MapObjectAddWindowFileOpenDialog:
						int index = Universe::instance->brushIndex;
						Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapObjectAddWindow + index)->remove();
						break;
				}
				break;
			}
			*/
			case EGET_FILE_SELECTED:
			{
				char filename[256];

				wcstombs(filename, ((IGUIFileOpenDialog*)event.GUIEvent.Caller)->getFileName(), 255);
				switch (eventCallerId)
				{
					case MapObjectEditWindowFileOpenDialog:
					{
						int index = Universe::instance->brushIndex;
						MapObject* mapObject;
						int mapObjectId;
						char path[256];

						IGUIWindow* wnd = (IGUIWindow*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapCellEditWindow + index, true);
						swscanf(wnd->getText(), L"[%d]", &mapObjectId);
						switch (index)
						{
							case 0:
								//Is not used. MapCell does not use models and textures
								break;
							case 1:
								mapObject = Universe::instance->game->resources->GetNPC(mapObjectId);
								sprintf(path, "editor/%s/model/NPC", Universe::instance->game->name);
								break;
							case 2:
								mapObject = Universe::instance->game->resources->GetStatic(mapObjectId);
								sprintf(path, "editor/%s/model/Static", Universe::instance->game->name);
								break;
							case 3:
								mapObject = Universe::instance->game->resources->GetItem(mapObjectId);
								sprintf(path, "editor/%s/model/Item", Universe::instance->game->name);
								break;
							case 4:
								mapObject = Universe::instance->game->resources->GetCharacter(mapObjectId);
								sprintf(path, "editor/%s/model/Character", Universe::instance->game->name);
								break;
						}
						ImportModel(filename, path, mapObject->id);
						mapObject->ModelInit(path);

						//Update mesh
						IGUIMeshViewer* mv = (IGUIMeshViewer*)wnd->getElementFromId(MapObjectEditWindowPreview);
						SMaterial* sm = new SMaterial();
						sm->setTexture(0, mapObject->texture);
						sm->setFlag(EMF_LIGHTING, false);
						mv->setMesh(mapObject->mesh);
						mv->setMaterial(*sm);

						//Update mesh
						IGUIMeshViewer* mv2 = (IGUIMeshViewer*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapObjectMeshViever, true);
						mv2->setMesh(mapObject->mesh);
						mv2->setMaterial(*sm);

						break;
					}
					case MapObjectAddWindowFileOpenDialog:
					{
						int index = Universe::instance->brushIndex;
						MapObject* mapObject;

						switch (index)
						{
							case 0:
								//Is not used. MapCell does not use models and textures
								//mapObject = Universe::instance->game->resources->AddMapCell("default name", "", filename, NULL);//texturePath is not used yet
								break;
							case 1:
								mapObject = Universe::instance->game->resources->AddNPC("default name", "", filename, NULL);//texturePath is not used yet
								break;
							case 2:
								mapObject = Universe::instance->game->resources->AddStatic("default name", "", filename, NULL);//texturePath is not used yet
								break;
							case 3:
								mapObject = Universe::instance->game->resources->AddItem("default name", "", filename, NULL);//texturePath is not used yet
								break;
							case 4:
								mapObject = Universe::instance->game->resources->AddCharacter("default name", "", filename, NULL);//texturePath is not used yet
								break;
						}

						/*
						//Open select window
						SEvent clickEvent;
						clickEvent.EventType = EET_GUI_EVENT;
						clickEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
						clickEvent.GUIEvent.Caller = Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapCellSelectWindowToggleButton + index, true); //->getElementFromId(ToolBarWindow)
						Universe::instance->render->device->postEventFromUser(clickEvent);
						*/
						break;
					}
				}
				break;
			}
			case EGET_BUTTON_CLICKED:
				switch (eventCallerId)
				{
					case MapObjectEditWindowOKButton:
						int mapObjectId;
						IGUIWindow* wnd;
						
						wnd = (IGUIWindow*)event.GUIEvent.Caller->getParent();
						swscanf(wnd->getText(), L"[%d]", &mapObjectId);

						switch (wnd->getID())
						{
							case MapCellEditWindow:
								MapCell* mapCell = Universe::instance->game->resources->GetMapCell(mapObjectId);
								//swscanf(, L"%d", &);
								wcstombs(mapCell->name, wnd->getElementFromId(MapObjectEditWindowName)->getText(), 255);
								break;
						}

						//Close edit window
						event.GUIEvent.Caller->getParent()->remove();
						break;
					case MapObjectSelectWindowToggleButton:
					{
						wchar_t wstr[512]; //Buffer
						MapObject** mapObjects; //General pointer to any MapObjects in GameResources. Is defined in the switch below
						int mapObjectsCount; //'mapObjects' count
						MapObject* selectedMapObject;
						int brushIndex; //Current brush (0: MapCell, 1:NPC, 2:Item, 3:Static, 4:Character)

						brushIndex = ((IGUITabControl*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapObjectsTabControl, true))->getActiveTab();

						switch (brushIndex)
						{
							case 0:
								//Define specific title
								wcscpy(wstr, L"Map cell selection");
								//Define that we would use MapCells as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->mapCells;
								mapObjectsCount = Universe::instance->game->resources->mapCellsCount;
								break;
							case 1:
								//Define specific title
								wcscpy(wstr, L"NPC selection");
								//Define that we would use NPCs as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->npcs;
								mapObjectsCount = Universe::instance->game->resources->npcsCount;
								break;
							case 2:
								//Define specific title
								wcscpy(wstr, L"Static selection");
								//Define that we would use Statics as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->statics;
								mapObjectsCount = Universe::instance->game->resources->staticsCount;
								break;
							case 3:
								//Define specific title
								wcscpy(wstr, L"Item selection");
								//Define that we would use Items as MapObjects
								mapObjects = (MapObject**)Universe::instance->game->resources->items;
								mapObjectsCount = Universe::instance->game->resources->itemsCount;
								break;
							case 4:
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
						wnd1 = Universe::instance->guienv->addWindow(rect< s32 >(224, 64, 760, 536), true, wstr, 0, MapCellSelectWindow + brushIndex);

						//ListBox for MapObjects
						IGUIListBox* molb = Universe::instance->guienv->addListBox(rect< s32 >(128, 64, 128 + 224, 64 + 320), wnd1, MapObjectSelectWindowListBox, true);
						for (int index = 0; index < mapObjectsCount; index++)
						{
							swprintf(wstr, L"[%d] ", mapObjects[index]->id);
							mbstowcs(wstr + wcslen(wstr), mapObjects[index]->name, 511);
							molb->addItem(wstr);
							if (Universe::instance->brush[brushIndex] == mapObjects[index])
								molb->setSelected(index); //Select item in list that was used last time in this MapObject list
						}
						if (molb->getSelected() >= 0)
						{
							int selectedMapObjectId;
							swscanf(molb->getListItem(molb->getSelected()), L"[%d]", &selectedMapObjectId);
							selectedMapObject = Universe::instance->game->resources->GetMapObject(mapObjects, mapObjectsCount, selectedMapObjectId);
						}
						else
						{
							selectedMapObject = NULL;
						}

						tagsCount = Universe::instance->game->resources->GetMapObjectsTags(mapObjects, mapObjectsCount, tags);
						if (tagsCount > 0)
						{ //Tags exists. Therefore we're to put 'All' CheckBox
							Universe::instance->guienv->addCheckBox(true, rect< s32 >(32, 64, 32 + 92, 64 + 16), wnd1, -1, L"All");
							for (int i = 0; i < tagsCount; i++)
							{
								mbstowcs(wstr, tags[i], 511);
								Universe::instance->guienv->addCheckBox(true, rect< s32 >(32, 80 + 16 * i, 32 + 92, 80 + 16 * (i + 1)), wnd1, -1, wstr);
							}
							delete[] tags;
						}

						//Preview
						CGUIMeshViewer* mv = new CGUIMeshViewer(Universe::instance->guienv, wnd1, MapObjectMeshViever, rect< s32 >(364, 64, 364 + 160, 64 + 256));
						if (selectedMapObject)
						{
							IAnimatedMesh* mesh = selectedMapObject->mesh;
							SMaterial* sm = new SMaterial();
							sm->setTexture(0, selectedMapObject->texture);
							sm->setFlag(EMF_LIGHTING, false);
							mv->setMesh(mesh);
							mv->setMaterial(*sm);
						}
						
						Universe::instance->guienv->addButton(rect< s32 >(311, 420, 311 + 96, 420 + 32), wnd1, MapObjectEditButton, L"Edit", L"Edit current map object");

						Universe::instance->guienv->addButton(rect< s32 >(415, 420, 415 + 96, 420 + 32), wnd1, MapObjectSelectWindowOKButton, L"OK", L"Select current map object");
						break;
					}
					case MapObjectSelectWindowOKButton:
					{
						int index = eventCaller->getParent()->getID() - MapCellSelectWindow;
						IGUIListBox* lb = (IGUIListBox*)eventCaller->getParent()->getElementFromId(MapObjectSelectWindowListBox);
						if (lb->getSelected() >= 0)
						{
							int mapObjectId;
							swscanf(lb->getListItem(lb->getSelected()), L"[%d]", &mapObjectId);
							switch (index)
							{
								case 0:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetMapCell(mapObjectId);
									break;
								case 1:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetNPC(mapObjectId);
									break;
								case 2:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetItem(mapObjectId);
									break;
								case 3:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetStatic(mapObjectId);
									break;
								case 4:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetCharacter(mapObjectId);
									break;
							}
							//Close parent window (MapObject selection window)
							lb->getParent()->remove();
						}
						break;
					}
					case MapObjectEditWindowImportModelButton:
						Universe::instance->guienv->addFileOpenDialog(L"Model file", true, NULL, MapObjectEditWindowFileOpenDialog);
						break;
					case MapObjectEditButton:
					{
						IGUIListBox* lb = (IGUIListBox*)eventCaller->getParent()->getElementFromId(MapObjectSelectWindowListBox);
						if (lb->getSelected() >= 0)
						{
							int index = eventCaller->getParent()->getID() - MapCellSelectWindow;

							//Window
							wchar_t wstr[256];
							swprintf(wstr, L"%s - editing", lb->getListItem(lb->getSelected()));
							IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect< s32 >(224 + 32, 64 + 32, 760 + 32, 536 + 32), true, wstr, NULL, MapCellEditWindow + index);
							//Universe::instance->guienv->setFocus(wnd);

							//Name
							IGUIEditBox* neb = Universe::instance->guienv->addEditBox(NULL, rect< s32 >(32, 32, 32 + 128, 32 + 24), true, wnd, MapObjectEditWindowName);
							Universe::instance->guienv->setFocus(neb);
					
							//Tags
							Universe::instance->guienv->addEditBox(NULL, rect< s32 >(32, 32 + 24 + 8, 32 + 128, 32 + 24 + 24 + 8), true, wnd, MapObjectEditWindowTags);
					
							//Preview
							CGUIMeshViewer* mv = new CGUIMeshViewer(Universe::instance->guienv, wnd, MapObjectEditWindowPreview, rect< s32 >(32 + 128 + 8, 32, 32 + 128 + 8 + 256, 32 + 320));
							MapObject* mapObject;
							int mapObjectId;
							swscanf(wnd->getText(), L"[%d]", &mapObjectId);
							switch (index)
							{
								case 0:
									mapObject = Universe::instance->game->resources->GetMapCell(mapObjectId);
									break;
								case 1:
									mapObject = Universe::instance->game->resources->GetNPC(mapObjectId);
									break;
								case 2:
									mapObject = Universe::instance->game->resources->GetStatic(mapObjectId);
									break;
								case 3:
									mapObject = Universe::instance->game->resources->GetItem(mapObjectId);
									break;
								case 4:
									mapObject = Universe::instance->game->resources->GetCharacter(mapObjectId);
									break;
							}
							SMaterial* sm = new SMaterial();
							sm->setTexture(0, mapObject->texture);
							sm->setFlag(EMF_LIGHTING, false);
							mv->setMesh(mapObject->mesh);
							mv->setMaterial(*sm);
							
							//Model selection button
							Universe::instance->guienv->addButton(rect< s32 >(32 + 128 + 8, 32 + 320 + 8, 32 + 128 + 8 + 256, 32 + 320 + 8 + 24), wnd, MapObjectEditWindowImportModelButton, L"Select model", NULL);

							//OK
							Universe::instance->guienv->addButton(rect< s32 >(536 - 20 - 92, 472 - 20 - 32, 536 - 20, 472 - 20), wnd, MapObjectEditWindowOKButton, L"OK", L"Add element and close the window");

							switch (index)
							{
								case 0:
									break;
								case 1:
									
									break;
								case 2:
									
									break;
								case 3:
									
									break;
								case 4:
									
									break;
							}
						}
						break;
					}
					case MapObjectAddButton:
						Universe::instance->guienv->addFileOpenDialog(L"Model file", true, NULL, MapObjectAddWindowFileOpenDialog);
						break;
					case LocationsEditButton:
					{
						IGUIWindow* wnd;
						wnd = Universe::instance->guienv->addWindow(rect< s32 >(Universe::instance->toolbarWidth, 0, Universe::instance->toolbarWidth + 242, 184), true, L"Locations edit", 0, LocationsEditWindow);
						wnd->setDraggable(false);
						Universe::instance->guienv->addEditBox(Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(LocationsComboBox)->getText(), rect< s32 >(32, 32, 208, 56), true, wnd, LocationNameEditBox);
						Universe::instance->guienv->addEditBox(L"64", rect< s32 >(32, 80, 112, 104), true, wnd, LocationWidthEditBox);
						Universe::instance->guienv->addEditBox(L"64", rect< s32 >(128, 80, 208, 104), true, wnd, LocationHeightEditBox);
						Universe::instance->guienv->addButton(rect< s32 >(32, 128, 32 + 48, 160), wnd, LocationsEditDeleteButton, L"Delete", L"Delete current location");
						Universe::instance->guienv->addButton(rect< s32 >(96, 128, 96 + 48, 160), wnd, LocationsEditSaveButton, L"Save", L"Apply settings to the current location")->setEnabled(false);
						Universe::instance->guienv->addButton(rect< s32 >(160, 128, 160 + 48, 160), wnd, LocationsEditAddButton, L"Save as", L"Apply settings to the new location");
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

bool EditorEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool EditorEventReceiver::isMouseDown(EKEY_CODE mouseCode) const
{
	return Mouse[mouseCode];
}

EditorEventReceiver::EditorEventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	for (u32 i = 0; i < EMIE_COUNT; ++i)
		Mouse[i] = false;
}
