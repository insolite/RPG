#pragma once

template<class T> //T inherits MapObject
class __declspec(dllexport) CurrentGameObject
{
public:
	int id; //objectId
	T* base; //pointer to NPC, Static, or Item
	
	void virtual Update() = 0;

	CurrentGameObject(SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount);
	CurrentGameObject(char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount);
	~CurrentGameObject(void);
};

