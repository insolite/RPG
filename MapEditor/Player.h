#pragma once
#include "Actor.h"
#include "Item.h"
using namespace std;

class Player :
	public Actor,
	public MapObject
{
public:
	Player(void);
	~Player(void);
};

