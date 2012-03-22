#pragma once
#include "Actor.h"
#include "Item.h"

class Character :
	public Actor,
	public MapObject
{
public:
	__declspec(dllexport) Character(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~Character(void);
};
