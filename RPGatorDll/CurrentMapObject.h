#pragma once
#include "Render.h"

template<class T> //T inherits MapObject
class __declspec(dllexport) CurrentMapObject :
	public CurrentGameObject<T>
{
public:
	f32 x;
	f32 y;
	Location* currentLocation; //Cross-link. Client does not use it. It uses Universe->currentLocation
	ISceneNode* node;
	ISceneNode* title;

	void setTitle(char* text);
	void setAnimation(EMD2_ANIMATION_TYPE animationType);

	CurrentMapObject(SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount, Location* location);
	CurrentMapObject(char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount);
	~CurrentMapObject(void);
};
