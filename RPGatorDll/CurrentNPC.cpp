#include "StdAfx.h"
#include "CurrentNPC.h"

CurrentNPC::CurrentNPC(std::map<std::string, std::string> strings, std::map<std::string, int> integers) : CurrentMapObject<NPC>::CurrentMapObject(strings, integers)
{
}

CurrentNPC::~CurrentNPC(void)
{
}
