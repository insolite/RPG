#pragma once
#include "Actor.h"
#include "Sprite.h"
#include "MapObject.h"

class NPC :
	public Actor,
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//NPC(int _id);
	__declspec(dllexport) NPC(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~NPC(void);
};

