#pragma once
#include "CurrentMapObject.h"
#include "NPC.h"

class CurrentNPC : CurrentMapObject<NPC>
{
public:
	__declspec(dllexport) CurrentNPC(NPC* base, int x, int y);
	__declspec(dllexport) ~CurrentNPC(void);
};
