#pragma once
#include "Actor.h"
#include "Item.h"

class Player :
	public Actor,
	public MapObject
{
public:
	__declspec(dllexport) Player(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~Player(void);
};
