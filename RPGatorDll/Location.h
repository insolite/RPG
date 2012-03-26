#pragma once

class Location
{
public:
	MapCell*** mask; //Not CurrentMapCell
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

	template<class T>
	__declspec(dllexport) void CurrentMapObjectsInit(T** &currentMapObjects, int &currentMapObjectsCount, char* tableName);
	__declspec(dllexport) void AddNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) void AddCurrentCharacter(CurrentCharacter* currentCharacter);

	template<class T>
	__declspec(dllexport) T* GetCurrentMapObject(T** currentMapObjects, int currentMapObjectsCount, int id);

	//__declspec(dllexport) Location(int _id);
	__declspec(dllexport) Location(SqliteResult sqliteResult, InitializationType initializationType); //Init for MapEditor
	__declspec(dllexport) ~Location(void);
};
