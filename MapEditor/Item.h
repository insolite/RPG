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

	Item(void);
	~Item(void);
};

