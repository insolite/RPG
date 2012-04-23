#pragma once

class CurrentNPC :
	public CurrentMapObject<NPC>
{
public:
	__declspec(dllexport) void Update();

	__declspec(dllexport) CurrentNPC(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentNPC(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentNPC(void);
};
