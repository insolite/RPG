#include "StdAfx.h"
#include "CurrentCharacter.h"

CurrentCharacter::CurrentCharacter(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : CurrentMapObject<Character>::CurrentMapObject(strings, integers)
{
	login = new char[strings["login"].length() + 1];
	strcpy(login, strings["login"].c_str());
	password = new char[strings["password"].length() + 1];
	strcpy(password, strings["password"].c_str());

	//TODO: Find base
	//base = 
}

CurrentCharacter::~CurrentCharacter(void)
{
	delete login;
	delete password;
}
