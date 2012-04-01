#pragma once

class Location
{
public:
	MapCell*** mask; //Not CurrentMapCell**
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
	__declspec(dllexport) void AddNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) void AddStatic(CurrentStatic* currentStatic);
	__declspec(dllexport) void AddItem(CurrentItem* currentItem);
	__declspec(dllexport) void AddCharacter(CurrentCharacter* currentCharacter);

	template<class T>
	__declspec(dllexport) T* GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id);

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
