#include "Sprite.h"
#pragma once

class Item
{
public:
	Sprite *iconSprite,
		   *groundSprite,
		   *equipSprite;

	Item(void);
	~Item(void);
};

