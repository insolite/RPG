#pragma once

class __declspec(dllexport) GameResources
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
	T* GetMapObject(T** mapObjects, int mapObjectsCount, int id) //TODO: move implementation to source file
	{
		for (int i = 0; i < mapObjectsCount; i++)
			if (mapObjects[i]->id == id)
				return mapObjects[i];
		return NULL;
	}
	MapCell* GetMapCell(int id);
	NPC* GetNPC(int id);
	Static* GetStatic(int id);
	Item* GetItem(int id);
	Character* GetCharacter(int id);
	Skill* GetSkill(int id);
	//We are using add methods only for editor, so we don't need to implement spawn methods as it did in GameData. We can do it in add method as well
	NPC* AddNPC(char* name, char* tags, char* modelPath, char* texturePath);
	Static* AddStatic(char* name, char* tags, char* modelPath, char* texturePath);
	Item* AddItem(char* name, char* tags, char* modelPath, char* texturePath);
	Character* AddCharacter(char* name, char* tags, char* modelPath, char* texturePath);

	template<class T>
	T** FilterByTag(T** mapObjects, int mapObjectsCounter, char** tag, int numberOfTags);
	int GetMapObjectsTags(MapObject** mapObjects, int mapObjectsCount, char** &tags); /*
																											Seachs for all unique tags in 'mapObjects' and creates new char** array of pointers on them
																											Return value: The found tags count
																											Warning! You're only to delete the top pointer on array, but not each pointer on char array, because they points to the real tags in MapObjects and is not duplicated
																											*/
	GameResources(InitializationType initializationType);
	~GameResources(void);

private:
	template<class T>
	void MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName, InitializationType initializationType);
	template<class T>
	void GameObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName, InitializationType initializationType);
	template<class T>
	void SpawnMapObject(T** &mapObjects, int &mapObjectsCount, T* mapObject);
	template<class T>
	T* AddMapObject(T** &mapObjects, int &mapObjectsCount, char* tableName, char* modelPath);
};
