#pragma once
#include "CurrentMapObject.h"
#include "NPC.h"

class CurrentNPC : CurrentMapObject<NPC>
{
public:
	__declspec(dllexport) CurrentNPC(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~CurrentNPC(void);
};
