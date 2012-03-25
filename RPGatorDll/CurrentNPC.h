#pragma once
#include "CurrentMapObject.h"
#include "NPC.h"
//#include "Game.h"

class CurrentNPC : CurrentMapObject<NPC>
{
public:
	__declspec(dllexport) CurrentNPC(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~CurrentNPC(void);

	//int id;
	//int xPos;
	//int yPos;
	//int hp;
	//NPC* bace;
	//Sprite* sprite;
};
