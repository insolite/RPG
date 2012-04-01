#pragma once

class GameResources
{
public:
	MapCell** mapCells;
	NPC** npcs;
	Static** statics;
	Item** items;
	Character** characters;

	Quest** quests;
	Skill** skills;
	
	int mapCellsCount;
	int npcsCount;
	int staticsCount;
	int itemsCount;
	int charactersCount;

	int questsCount;
	int skillsCount;

	template<class T>
	__declspec(dllexport) T* GetMapObject(T** mapObjects, int mapObjectsCount, int id)
	{
		for (int i = 0; i < mapObjectsCount; i++)
			if (mapObjects[i]->id == id)
				return mapObjects[i];
		return NULL;
	}
	__declspec(dllexport) MapCell* GetMapCell(int id);
	__declspec(dllexport) NPC* GetNPC(int id);
	__declspec(dllexport) Static* GetStatic(int id);
	__declspec(dllexport) Item* GetItem(int id);
	__declspec(dllexport) Character* GetCharacter(int id);
	template<class T>
	__declspec(dllexport) T** FilterByTag(T** mapObjects, int mapObjectsCounter, char** tag, int numberOfTags);
	__declspec(dllexport) int GetMapObjectsTags(MapObject** mapObjects, int mapObjectsCount, char** &tags); /*
																											Seachs for all unique tags in 'mapObjects' and creates new char** array of pointers on them
																											Return value: The found tags count
																											Warning! You're only to delete the top pointer on array, but not each pointer on char array, because they points to the real tags in MapObjects and is not duplicated
																											*/
	__declspec(dllexport) GameResources(void);
	__declspec(dllexport) ~GameResources(void);

private:
	template<class T>
	__declspec(dllexport) void MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName);
};
