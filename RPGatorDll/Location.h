#pragma once

enum CellProperty { Free = 0, Locked, Transparment };

class __declspec(dllexport) Location
{
public:
	CellProperty** mask;
	CurrentNPC** currentNPCs;
	CurrentStatic** currentStatics;
	CurrentItem** currentItems;
	CurrentCharacter** currentCharacters;
	int currentNPCsCount;
	int currentStaticsCount;
	int currentItemsCount;
	int currentCharactersCount;

	int width, height;
	int id;
	char *name;

	void Update();
	void SpawnNPC(CurrentNPC* currentNPC);
	void SpawnStatic(CurrentStatic* currentStatic);
	void SpawnItem(CurrentItem* currentItem);
	void SpawnCharacter(CurrentCharacter* currentCharacter);
	void UnSpawnNPC(CurrentNPC* currentNPC);
	void UnSpawnStatic(CurrentStatic* currentStatic);
	void UnSpawnItem(CurrentItem* currentItem);
	void UnSpawnCharacter(CurrentCharacter* currentCharacter);
	void DeleteNPC(CurrentNPC* currentNPC);
	void DeleteStatic(CurrentStatic* currentStatic);
	void DeleteItem(CurrentItem* currentItem);
	void DeleteCharacter(CurrentCharacter* currentCharacter);
	CurrentNPC* AddNPC(NPC* base, f32 x, f32 y);
	CurrentStatic* AddStatic(Static* base, f32 x, f32 y);
	CurrentItem* AddItem(Item* base, f32 x, f32 y, int count);
	CurrentCharacter* AddCharacter(Character* base, f32 x, f32 y, char* login, char* password);
	/*
	CurrentNPC* GetNPCAt(int x, int y);
	CurrentStatic* GetStaticAt(int x, int y);
	CurrentItem* GetItemAt(int x, int y);
	CurrentCharacter* GetCharacterAt(int x, int y);
	*/
	CurrentNPC* GetNPC(int id);
	CurrentStatic* GetStatic(int id);
	CurrentItem* GetItem(int id);
	CurrentCharacter* GetCharacter(int id);
	template<class T>
	T* GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id);
	template<class T>
	T* GetCurrentMapObjectAt(T** currentMapObjects, int currentMapObjectsCount, int x, int y);

	Location(SqliteResult sqliteResult, InitializationType initializationType);
	~Location(void);
private:
	template<class T>
	void CurrentMapObjectsInit(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName);
	template<class T>
	void SpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject);
	template<class T>
	void UnSpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject);
	template<class T>
	void DeleteCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName, T* currentMapObject);
};
