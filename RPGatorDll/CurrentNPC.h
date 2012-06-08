#pragma once

class __declspec(dllexport) CurrentNPC :
	public CurrentMapObject<NPC>
{
public:
	void Update();


	CurrentNPC(SqliteResult sqliteResult, Location* location);
	CurrentNPC(char* currentMapObjectSpawnedPacket);
	~CurrentNPC(void);
};
