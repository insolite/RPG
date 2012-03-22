#pragma once
#include "Sprite.h"

template<class T> //T inherits MapObject
class CurrentMapObject
{
public:
	int id; //objectId
	int x; //in "our" coordinates, not in pixels
	int y; //in "our" coordinates, not in pixels
	T* base; //pointer to NPC, Static, or Item
	Sprite* sprite;
	
	__declspec(dllexport) CurrentMapObject(std::map<std::string, std::string> strings, std::map<std::string, int> integers)
	{
		id = integers["id"];
		//x = integers["x"];
		//y = integers["y"];
		//sprite = new Sprite(base->SpriteBase);
	}

	__declspec(dllexport) ~CurrentMapObject(void)
	{
	}
};
