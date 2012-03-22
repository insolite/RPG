#pragma once
#include "MapCell.h"
#include "CurrentNPC.h"
#include "CurrentCharacter.h"

class Location
{
public:
	MapCell*** mask; //Not CurrentMapCell
	//CurrentNPC** currentNPCs;
	//CurrentStatic** currentStatics;
	//CurrentItem** currentItems;
	CurrentCharacter** currentCharacters;
	int currentCharactersCount;

	int width, height;
	int id;
	char *name;

	__declspec(dllexport) void AddNPC(CurrentNPC* currentNPC);
	__declspec(dllexport) bool AddCurrentCharacter(CurrentCharacter* currentCharacter);

	//__declspec(dllexport) Location(int _id);
	__declspec(dllexport) Location(std::map<std::string, std::string> strings, std::map<std::string, int> integers); //Init for MapEditor
	__declspec(dllexport) ~Location(void);
};
