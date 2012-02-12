#pragma once
#include "Sprite.h"
#include "MapObject.h"

class Item :
	public MapObject
{
public:
	Sprite *iconSprite,
		   *groundSprite,
		   *equipSprite;

	void Abstr ( void ) { }; //Abstract class inheritance

	Item(void);
	~Item(void);
};

