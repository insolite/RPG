#pragma once
#include "Sprite.h"

template<class T> //T inherits MapObject
class CurrentMapObject
{
public:
	int objectId;
	Sprite* sprite;
	int x; //in "our" coordinates, not in pixels
	int y; //in "our" coordinates, not in pixels
	T* base; //pointer to NPC, Static, or Item

	CurrentMapObject(T* _base, int _x, int _y)
	{
		base = _base;
		//sprite = new Sprite(base->SpriteBase);
		x = _x;
		y = _y;
		//TODO: generate unique objectId
	}

	~CurrentMapObject(void)
	{
	}
};
