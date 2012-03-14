#pragma once
#include "CurrentMapObject.h"
#include "NPC.h"

class CurrentNPC : CurrentMapObject<NPC>
{
public:
	CurrentNPC(NPC* base, int x, int y);
	~CurrentNPC(void);
};
