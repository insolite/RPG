#pragma once
#include "Actor.h"
#include "Sprite.h"
#include "MapObject.h"

class NPC :
	public Actor,
	public MapObject
{
public:
	void Abstr ( void ) { }; //Abstract class inheritance

	NPC(int _id);
	~NPC(void);
};

