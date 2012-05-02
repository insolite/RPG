#pragma once

enum CellProperty { Free = 0, Locked, Transparment };

class Location
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

	__declspec(dllexport) void Update();
	__declspec(dllexport) void SpawnNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) void SpawnStatic(CurrentStatic* currentStatic);
	__declspec(dllexport) void SpawnItem(CurrentItem* currentItem);
	__declspec(dllexport) void SpawnCharacter(CurrentCharacter* currentCharacter);
	__declspec(dllexport) void UnSpawnNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) void UnSpawnStatic(CurrentStatic* currentStatic);
	__declspec(dllexport) void UnSpawnItem(CurrentItem* currentItem);
	__declspec(dllexport) void UnSpawnCharacter(CurrentCharacter* currentCharacter);
	__declspec(dllexport) void DeleteNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) void DeleteStatic(CurrentStatic* currentStatic);
	__declspec(dllexport) void DeleteItem(CurrentItem* currentItem);
	__declspec(dllexport) void DeleteCharacter(CurrentCharacter* currentCharacter);
	__declspec(dllexport) CurrentNPC* AddNPC(NPC* base, double x, double y);
	__declspec(dllexport) CurrentStatic* AddStatic(Static* base, double x, double y);
	__declspec(dllexport) CurrentItem* AddItem(Item* base, double x, double y, int count);
	__declspec(dllexport) CurrentCharacter* AddCharacter(Character* base, double x, double y, char* login, char* password);
	/*
	__declspec(dllexport) CurrentNPC* GetNPCAt(int x, int y);
	__declspec(dllexport) CurrentStatic* GetStaticAt(int x, int y);
	__declspec(dllexport) CurrentItem* GetItemAt(int x, int y);
	__declspec(dllexport) CurrentCharacter* GetCharacterAt(int x, int y);
	*/
	__declspec(dllexport) CurrentNPC* GetNPC(int id);
	__declspec(dllexport) CurrentStatic* GetStatic(int id);
	__declspec(dllexport) CurrentItem* GetItem(int id);
	__declspec(dllexport) CurrentCharacter* GetCharacter(int id);
	template<class T>
	__declspec(dllexport) T* GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id);
	template<class T>
	__declspec(dllexport) T* GetCurrentMapObjectAt(T** currentMapObjects, int currentMapObjectsCount, int x, int y);

	__declspec(dllexport) Location(SqliteResult sqliteResult, InitializationType initializationType);
	__declspec(dllexport) ~Location(void);
private:
	template<class T>
	__declspec(dllexport) void CurrentMapObjectsInit(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName);
	template<class T>
	__declspec(dllexport) void SpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject);
	template<class T>
	__declspec(dllexport) void UnSpawnCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, T* currentMapObject);
	template<class T>
	__declspec(dllexport) void DeleteCurrentMapObject(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName, T* currentMapObject);
};
