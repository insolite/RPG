#pragma once

class GameResources
{
public:
	MapCell** mapCells;
	NPC** npcs;
	Static** statics;
	Item** items;
	Character** characters;
	
	int mapCellsCount;
	int npcsCount;
	int staticsCount;
	int itemsCount;
	int charactersCount;
	
	template<class T>
	__declspec(dllexport) T* GetMapObject(T** mapObjects, int mapObjectsCount, int id)
	{
		for (int i = 0; i < mapObjectsCount; i++)
			if (mapObjects[i]->id == id)
				return mapObjects[i];
		return NULL;
	}

	__declspec(dllexport) GameResources(void);
	__declspec(dllexport) ~GameResources(void);

private:
	template<class T>
	__declspec(dllexport) void MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName);
};
