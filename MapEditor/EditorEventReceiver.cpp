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
		{
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
					if (!Universe::instance->menuGuienv->getRootGUIElement()->getElementFromId(eventCallerId - 10))
					{
						wchar_t wstr[512]; //Buffer
						MapObject** mapObjects; //General pointer to any MapObjects in GameResources. Is defined in the switch below
						int mapObjectsCount; //'mapObjects' count
						int brushIndex; //Current brush (0: MapCell, 1:NPC, 2:Item, 3:Static, 4:Character)

						brushIndex = MapCellSelectWindowToggleButton - eventCallerId;

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
							mbstowcs(wstr, mapObjects[i]->name, 511);
							molb->addItem(wstr);
							if (Universe::instance->brush[brushIndex] == mapObjects[i])
								molb->setSelected(i); //Select item in list that was used last time in this MapObject list
						}

						tagsCount = Universe::instance->game->resources->GetMapObjectsTags(mapObjects, mapObjectsCount, tags);
						if (tagsCount > 0)
						{//Tags exists. Therefore we're to put 'All' CheckBox
							Universe::instance->guienv->addCheckBox(true, rect< s32 >(32, 64, 32 + 92, 64 + 16), wnd1, -1, L"All");
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
					Universe::instance->guienv->setFocus(Universe::instance->menuGuienv->getRootGUIElement()->getElementFromId(eventCallerId - 10));
				}
				else
				{
					switch (eventCallerId)
					{
						case MapCellSelectWindowOKButton:
							//Universe::instance->currentLocation->mask[cursorY][cursorX] = 
							break;
						case NPCSelectWindowOKButton:
							//Universe::instance->currentLocation->AddNPC
							break;
						case ItemSelectWindowOKButton:
							//Universe::instance->currentLocation->AddItem
							break;
						case StaticSelectWindowOKButton:
							//Universe::instance->currentLocation->AddStatic
							break;
						case CharacterSelectWindowOKButton:
							//Universe::instance->currentLocation->AddCharacter
							break;
					}
				}
				break;
			case EGET_COMBO_BOX_CHANGED:
				switch (eventCallerId)
				{
					case LocationsComboBox:
						Universe::instance->SetLocation(Universe::instance->game->data->locations[Universe::instance->locationsComboBox->getSelected()]);
						break;
				}
				break;
			case EGET_CHECKBOX_CHANGED:
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
