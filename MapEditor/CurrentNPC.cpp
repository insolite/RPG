#include "StdAfx.h"
#include "CurrentNPC.h"

CurrentNPC::CurrentNPC(NPC* base, int x, int y) : CurrentMapObject<NPC>::CurrentMapObject(base, x, y)
{
}

CurrentNPC::~CurrentNPC(void)
{
}
