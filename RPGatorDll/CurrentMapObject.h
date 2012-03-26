#pragma once

template<class T> //T inherits MapObject
class CurrentMapObject
{
public:
	int id; //objectId
	int x; //in "our" coordinates, not in pixels
	int y; //in "our" coordinates, not in pixels
	Location* currentLocation; //Cross-link. Client does not use it. It uses Universe->currentLocation
	T* base; //pointer to NPC, Static, or Item
	Sprite* sprite;
	
	__declspec(dllexport) CurrentMapObject(SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount, Location* location)
	{
		id = sqliteResult.integers["id"];
		x = sqliteResult.integers["x"];
		y = sqliteResult.integers["y"];
		currentLocation = location;
		//sprite = new Sprite(base->SpriteBase);
		base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, sqliteResult.integers["baseId"]);
	}

	__declspec(dllexport) CurrentMapObject(char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount)
	{
		id = PacketGetInt(currentMapObjectSpawnedPacket, 1);
		x = PacketGetInt(currentMapObjectSpawnedPacket, 9);
		y = PacketGetInt(currentMapObjectSpawnedPacket, 13);
		currentLocation = NULL; //Client does not use it. It uses Universe->currentLocation
		//sprite = new Sprite(base->SpriteBase);
		base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, PacketGetInt(currentMapObjectSpawnedPacket, 5));
		//Game::instance->resources->GetMapObject<Character>(1);
	}

	__declspec(dllexport) ~CurrentMapObject(void)
	{
	}
};
