#pragma once
#include "Render.h"

template<class T> //T inherits MapObject
class CurrentMapObject :
	public CurrentGameObject<T>
{
public:
	int x; //in "our" coordinates, not in pixels
	int y; //in "our" coordinates, not in pixels
	Location* currentLocation; //Cross-link. Client does not use it. It uses Universe->currentLocation
	ISceneNode* node;
	
	__declspec(dllexport) CurrentMapObject(SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount, Location* location) :
		CurrentGameObject<T>::CurrentGameObject(sqliteResult, mapObjects, mapObjectsCount)
	{
		x = sqliteResult.integers["x"];
		y = sqliteResult.integers["y"];
		currentLocation = location;
	}

	__declspec(dllexport) CurrentMapObject(char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount) :
		CurrentGameObject<T>::CurrentGameObject(currentMapObjectSpawnedPacket, mapObjects, mapObjectsCount)
	{
		x = PacketGetInt(currentMapObjectSpawnedPacket, 9);
		y = PacketGetInt(currentMapObjectSpawnedPacket, 13);
		currentLocation = NULL; //Client does not use it. It uses Universe->currentLocation
		node = Render::instance->createNode(true, "faerie.md2", "Faerie5.BMP", false, vector3df(0.5, 0.5, 0.5), vector3df(x * CELL_SIZE, 0.0f, y * CELL_SIZE));
	}

	__declspec(dllexport) ~CurrentMapObject(void)
	{
	}
};
