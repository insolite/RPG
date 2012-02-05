#include "Actor.h"
#include "Sprite.h"
#pragma once

class NPC :
	public Actor
{
public:
	Sprite* sprite;

	NPC(void);
	~NPC(void);
};

