#pragma once
#include "Actor.h"
#include "Sprite.h"
#include "MapObject.h"

class NPC :
	public Actor,
	public MapObject
{
public:
	Sprite* sprite;

	NPC(void);
	~NPC(void);
};

