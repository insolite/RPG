#include "Actor.h"
#include "Sprite.h"
#pragma once

class Npc :
	public Actor
{
public:
	Sprite* sprite;

	Npc(void);
	~Npc(void);
};

