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
			switch (Universe::instance->brushIndex)
			{
				case 0: //MapCell
					//Universe::instance->currentLocation->mask[y][x] = (MapCell*)Universe::instance->brush[0];
					//TODO: Save location before exit
					break;
				case 1: //NPC
					Universe::instance->currentLocation->AddNPC((NPC*)Universe::instance->brush[1], x, y);
					break;
				case 2: //Static
					Universe::instance->currentLocation->AddStatic((Static*)Universe::instance->brush[2], x, y);
					break;
				case 3: //Item
					Universe::instance->currentLocation->AddItem((Item*)Universe::instance->brush[3], x, y, 1);
					break;
				case 4: //Character
					Universe::instance->currentLocation->AddCharacter((Character*)Universe::instance->brush[4], x, y, "", "");
					break;
			}
		}
		else if (Mouse[EMIE_RMOUSE_PRESSED_DOWN])
		{ //Delete CurrentMapObject
			CurrentMapObject<MapObject>* deletingCurrentMapObject;
			if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentNPC>(Universe::instance->currentLocation->currentNPCs, Universe::instance->currentLocation->currentNPCsCount))
				Universe::instance->currentLocation->DeleteNPC((CurrentNPC*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentStatic>(Universe::instance->currentLocation->currentStatics, Universe::instance->currentLocation->currentStaticsCount))
				Universe::instance->currentLocation->DeleteStatic((CurrentStatic*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentItem>(Universe::instance->currentLocation->currentItems, Universe::instance->currentLocation->currentItemsCount))
				Universe::instance->currentLocation->DeleteItem((CurrentItem*)deletingCurrentMapObject);
			else if (deletingCurrentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentCharacter>(Universe::instance->currentLocation->currentCharacters, Universe::instance->currentLocation->currentCharactersCount))
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
		else if (Mouse[EMIE_MMOUSE_PRESSED_DOWN])
		{
			wchar_t wstr[512];
			int index;
			CurrentMapObject<MapObject>* currentMapObject;

			if (currentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentNPC>(Universe::instance->currentLocation->currentNPCs, Universe::instance->currentLocation->currentNPCsCount))
			{
				index = 1;
			}
			else if (currentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentStatic>(Universe::instance->currentLocation->currentStatics, Universe::instance->currentLocation->currentStaticsCount))
			{
				index = 2;
			}
			else if (currentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentItem>(Universe::instance->currentLocation->currentItems, Universe::instance->currentLocation->currentItemsCount))
			{
				index = 3;
			}
			else if (currentMapObject = (CurrentMapObject<MapObject>*)Universe::instance->render->GetCurrentMapObjectUnderCursor<CurrentCharacter>(Universe::instance->currentLocation->currentCharacters, Universe::instance->currentLocation->currentCharactersCount))
			{
				index = 4;
			}

			if (currentMapObject)
			{
				//Window
				wchar_t wstr2[256];
				mbstowcs(wstr2, currentMapObject->base->name, 255);
				swprintf(wstr, L"[%d] ([%d] %s) - editing", currentMapObject->id, currentMapObject->base->id, wstr2);
				IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect< s32 >(224 + 32, 64 + 32, 760 + 32, 536 + 32), true, wstr, NULL, CurrentMapCellEditWindow + index);
				/*
				//Name
				mbstowcs(wstr, mapObject->name, 255);
				IGUIEditBox* neb = Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32, 32 + 128, 32 + 24), true, wnd, MapObjectEditWindowName);
				Universe::instance->guienv->setFocus(neb);

				//Tags
				if (mapObject->tagsCount < 1)
					wcscpy(wstr, L"");
				else
					mbstowcs(wstr, mapObject->tags[0], 31);
				for (int i = 1; i < mapObject->tagsCount; i++)
				{
					wcscat(wstr, L",");
					mbstowcs(wstr + wcslen(wstr), mapObject->tags[i], 31);
				}
				IGUIEditBox* teb = Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32 + 24 + 8, 32 + 128, 32 + 24 + 24 + 8), true, wnd, MapObjectEditWindowTags);
				*/
				/*
				//Preview
				CGUIMeshViewer* mv = new CGUIMeshViewer(Universe::instance->guienv, wnd, MapObjectEditWindowPreview, rect< s32 >(32 + 128 + 8, 32, 32 + 128 + 8 + 256, 32 + 320));
				SMaterial* sm = new SMaterial();
				sm->setTexture(0, currentMapObject->texture);
				sm->setFlag(EMF_LIGHTING, false);
				mv->setMesh(currentMapObject->mesh);
				mv->setMaterial(*sm);
				*/
				switch (index)
				{
					case 1:
					{
						CurrentNPC* currentNPC = (CurrentNPC*)currentMapObject;
						break;
					}
					case 2:
					{
						CurrentStatic* currentStatic = (CurrentStatic*)currentMapObject;
						break;
					}
					case 3:
					{
						CurrentItem* currentItem = (CurrentItem*)currentMapObject;
						break;
					}
					case 4:
					{
						CurrentCharacter* currentCharacter = (CurrentCharacter*)currentMapObject;
						wchar_t wstr[256];

						mbstowcs(wstr, currentCharacter->login, 255);
						Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32, 32 + 128, 32 + 24), true, wnd, CurrentMapObjectEditWindowLoginEditBox);
						mbstowcs(wstr, currentCharacter->password, 255);
						Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32 + 24 + 8, 32 + 128, 32 + 24 + 24 + 8), true, wnd, CurrentMapObjectEditWindowPasswordEditBox);
						break;
					}
				}

				//OK
				Universe::instance->guienv->addButton(rect< s32 >(536 - 20 - 92, 472 - 20 - 32, 536 - 20, 472 - 20), wnd, CurrentMapObjectEditWindowOKButton, L"OK", L"Add element and close the window");
			}
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
				switch (eventCallerId)
				{
					case LocationsEditWindow:
						((IGUIButton*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(LocationsEditButton, true))->setPressed(false);
						break;
				}
				/*
				if (eventCallerId >= MapCellSelectWindow && eventCallerId <= CharacterSelectWindow)
				{
					Universe::instance->render->smgr->setActiveCamera(Universe::instance->camera);
				}
				*/
				break;
			case EGET_FILE_SELECTED:
			{
				char filename[256];

				wcstombs(filename, ((CGUIFileOpenDialog*)eventCaller)->getFileName(), 255);
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
						mapObject->ModelUnLoad(); //TODO: Make a secure mesh reload with ImportModel
						ImportModel(filename, path, mapObject->id);
						mapObject->ModelInit(path); //TODO: move new mesh loading into MapObjectEditWindowOKButton click event. Here must be only the new mesh path selection

						//Update meshes

						//Create material
						SMaterial* sm = new SMaterial();
						sm->setTexture(0, mapObject->texture);
						sm->setFlag(EMF_LIGHTING, false);

						//Update mesh in edit window
						IGUIMeshViewer* mv = (IGUIMeshViewer*)wnd->getElementFromId(MapObjectEditWindowPreview);
						mv->setMesh(mapObject->mesh);
						mv->setMaterial(*sm);

						//TODO: move it into MapObjectEditWindowOKButton click event //TODO: //Update mesh in tab (toobar)
						//Update mesh in select window
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
					{
						int mapObjectId;
						MapObject* mapObject;
						IGUIWindow* wnd;
						
						wnd = (IGUIWindow*)event.GUIEvent.Caller->getParent();
						swscanf(wnd->getText(), L"[%d]", &mapObjectId);

						switch (wnd->getID())
						{
							case MapCellEditWindow:
							{
								mapObject = Universe::instance->game->resources->GetMapCell(mapObjectId);
								MapCell* mapCell = (MapCell*)mapObject;
								break;
							}
							case NPCEditWindow:
							{
								mapObject = Universe::instance->game->resources->GetNPC(mapObjectId);
								NPC* npc = (NPC*)mapObject;
								break;
							}
							case StaticEditWindow:
							{
								mapObject = Universe::instance->game->resources->GetStatic(mapObjectId);
								Static* _static = (Static*)mapObject;
								break;
							}
							case ItemEditWindow:
							{
								mapObject = Universe::instance->game->resources->GetItem(mapObjectId);
								Item* item = (Item*)mapObject;
								break;
							}
							case CharacterEditWindow:
							{
								mapObject = Universe::instance->game->resources->GetCharacter(mapObjectId);
								Character* character = (Character*)mapObject;
								for (int i = 0; i < Universe::instance->currentLocation->currentCharactersCount; i++)
									Universe::instance->currentLocation->currentCharacters[i]->setTitle(character->name);
								break;
							}
						}

						wcstombs(mapObject->name, wnd->getElementFromId(MapObjectEditWindowName)->getText(), 255);

						//TODO: tags update

						mapObject->Update();

						wchar_t wstr[256];
						swprintf(wstr, L"[%d] %s", mapObject->id, wnd->getElementFromId(MapObjectEditWindowName)->getText());
						IGUIListBox* lb = (IGUIListBox*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(MapCellSelectWindow + wnd->getID() - MapCellEditWindow, true)->getElementFromId(MapObjectSelectWindowListBox);
						lb->setItem(lb->getSelected(), wstr, -1);

						//Close edit window
						wnd->remove();
						break;
					}
					case CurrentMapObjectEditWindowOKButton:
					{
						int currentMapObjectId;
						//CurrentMapObject<MapObject>* currentMapObject;
						IGUIWindow* wnd;
						
						wnd = (IGUIWindow*)event.GUIEvent.Caller->getParent();
						swscanf(wnd->getText(), L"[%d]", &currentMapObjectId);

						switch (wnd->getID())
						{
							case CurrentNPCEditWindow:
							{
								CurrentNPC* currentNPC = Universe::instance->currentLocation->GetNPC(currentMapObjectId);
								currentNPC->Update();
								break;
							}
							case CurrentStaticEditWindow:
							{
								CurrentStatic* currentStatic = Universe::instance->currentLocation->GetStatic(currentMapObjectId);
								currentStatic->Update();
								break;
							}
							case CurrentItemEditWindow:
							{
								CurrentItem* currentItem = Universe::instance->currentLocation->GetItem(currentMapObjectId);
								currentItem->Update();
								break;
							}
							case CurrentCharacterEditWindow:
							{
								CurrentCharacter* currentCharacter = Universe::instance->currentLocation->GetCharacter(currentMapObjectId);
								wcstombs(currentCharacter->login, wnd->getElementFromId(CurrentMapObjectEditWindowLoginEditBox)->getText(), 255);
								wcstombs(currentCharacter->password, wnd->getElementFromId(CurrentMapObjectEditWindowPasswordEditBox)->getText(), 255);
								currentCharacter->setTitle(currentCharacter->login);
								currentCharacter->Update();
								break;
							}
						}

						//Close edit window
						wnd->remove();
						break;
					}
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
						wnd1 = Universe::instance->guienv->addWindow(rect< s32 >(224, 64, 760, 536), true, wstr, NULL, MapCellSelectWindow + brushIndex);

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
									Universe::instance->brush[index] = Universe::instance->game->resources->GetStatic(mapObjectId);
									break;
								case 3:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetItem(mapObjectId);
									break;
								case 4:
									Universe::instance->brush[index] = Universe::instance->game->resources->GetCharacter(mapObjectId);
									break;
							}

							CGUIMeshViewer* mv = (CGUIMeshViewer*)((IGUITabControl*)Universe::instance->guienv->getRootGUIElement()->getElementFromId(ToolBarWindow)->getElementFromId(MapObjectsTabControl))->getTab(index)->getElementFromId(MapObjectTabPreview);
							SMaterial* sm = new SMaterial();
							sm->setTexture(0, Universe::instance->brush[index]->texture);
							sm->setFlag(EMF_LIGHTING, false);
							mv->setMesh(Universe::instance->brush[index]->mesh);
							mv->setMaterial(*sm);

							//Close select window
							lb->getParent()->remove();
						}
						break;
					}
					case MapObjectEditWindowImportModelButton:
						(new CGUIFileOpenDialog(L"Model file", Universe::instance->guienv, Universe::instance->guienv->getRootGUIElement(), MapObjectEditWindowFileOpenDialog))->drop();
						break;
					case MapObjectEditButton:
					{
						IGUIListBox* lb = (IGUIListBox*)eventCaller->getParent()->getElementFromId(MapObjectSelectWindowListBox);
						if (lb->getSelected() >= 0)
						{
							wchar_t wstr[512];
							int index = eventCaller->getParent()->getID() - MapCellSelectWindow;

							//Window
							swprintf(wstr, L"%s - editing", lb->getListItem(lb->getSelected()));
							IGUIWindow* wnd = Universe::instance->guienv->addWindow(rect< s32 >(224 + 32, 64 + 32, 760 + 32, 536 + 32), true, wstr, NULL, MapCellEditWindow + index);
							
							//Preview
							CGUIMeshViewer* mv = new CGUIMeshViewer(Universe::instance->guienv, wnd, MapObjectEditWindowPreview, rect< s32 >(32 + 128 + 8, 32, 32 + 128 + 8 + 256, 32 + 320));
							MapObject* mapObject;
							int mapObjectId;
							swscanf(wnd->getText(), L"[%d]", &mapObjectId);
							switch (index)
							{
								case 0:
								{
									mapObject = Universe::instance->game->resources->GetMapCell(mapObjectId);
									MapCell* mapCell = (MapCell*)mapObject;

									//mbstowcs(wstr, mapCell->name, 255);
									//neb->setText(wstr);
									break;
								}
								case 1:
								{
									mapObject = Universe::instance->game->resources->GetNPC(mapObjectId);
									NPC* npc = (NPC*)mapObject;
									break;
								}
								case 2:
								{
									mapObject = Universe::instance->game->resources->GetStatic(mapObjectId);
									Static* _static = (Static*)mapObject;
									break;
								}
								case 3:
								{
									mapObject = Universe::instance->game->resources->GetItem(mapObjectId);
									Item* item = (Item*)mapObject;
									break;
								}
								case 4:
								{
									mapObject = Universe::instance->game->resources->GetCharacter(mapObjectId);
									Character* character = (Character*)mapObject;
									break;
								}
							}
							
							//Name
							mbstowcs(wstr, mapObject->name, 255);
							IGUIEditBox* neb = Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32, 32 + 128, 32 + 24), true, wnd, MapObjectEditWindowName);
							Universe::instance->guienv->setFocus(neb);

							//Tags
							if (mapObject->tagsCount < 1)
								wcscpy(wstr, L"");
							else
								mbstowcs(wstr, mapObject->tags[0], 31);
							for (int i = 1; i < mapObject->tagsCount; i++)
							{
								wcscat(wstr, L",");
								mbstowcs(wstr + wcslen(wstr), mapObject->tags[i], 31);
							}
							IGUIEditBox* teb = Universe::instance->guienv->addEditBox(wstr, rect< s32 >(32, 32 + 24 + 8, 32 + 128, 32 + 24 + 24 + 8), true, wnd, MapObjectEditWindowTags);
							
							SMaterial* sm = new SMaterial();
							sm->setTexture(0, mapObject->texture);
							sm->setFlag(EMF_LIGHTING, false);
							mv->setMesh(mapObject->mesh);
							mv->setMaterial(*sm);
							
							//Model selection button
							Universe::instance->guienv->addButton(rect< s32 >(32 + 128 + 8, 32 + 320 + 8, 32 + 128 + 8 + 256, 32 + 320 + 8 + 24), wnd, MapObjectEditWindowImportModelButton, L"Select model", NULL);

							//OK
							Universe::instance->guienv->addButton(rect< s32 >(536 - 20 - 92, 472 - 20 - 32, 536 - 20, 472 - 20), wnd, MapObjectEditWindowOKButton, L"OK", L"Add element and close the window");
						}
						break;
					}
					case MapObjectAddButton:
						(new CGUIFileOpenDialog(L"Model file", Universe::instance->guienv, Universe::instance->guienv->getRootGUIElement(), MapObjectAddWindowFileOpenDialog))->drop();
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
