#pragma once

template<class T> //T inherits MapObject
class CurrentGameObject
{
public:
	int id; //objectId
	T* base; //pointer to NPC, Static, or Item
	
	__declspec(dllexport) CurrentGameObject(SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount)
	{
		id = sqliteResult.integers["id"];
		base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, sqliteResult.integers["baseId"]);
	}

	__declspec(dllexport) CurrentGameObject(char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount)
	{
		id = PacketGetInt(currentMapObjectSpawnedPacket, 1);
		base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, PacketGetInt(currentMapObjectSpawnedPacket, 5));
	}

	__declspec(dllexport) ~CurrentGameObject(void)
	{
	}
};
