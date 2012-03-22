#pragma once
#include "CurrentMapObject.h"
#include "Character.h"

class CurrentCharacter :
	public CurrentMapObject<Character>
{
public:
	char* login;
	char* password;

	__declspec(dllexport) CurrentCharacter(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~CurrentCharacter(void);
};
