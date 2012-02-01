#pragma once
#include "Actor.h"
#include "Item.h"
using namespace std;

class Player :
	public Actor
{
public:
	vector<Item*> items;

	Player(void);
	~Player(void);
};

