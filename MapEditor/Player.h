#pragma once
#include "Actor.h"
#include "Item.h"

class Player :
	public Actor,
	public MapObject
{
public:
	Player(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	~Player(void);
};
