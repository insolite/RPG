#pragma once

class CurrentStatic :
	public CurrentMapObject<Static>
{
public:
	__declspec(dllexport) CurrentStatic(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentStatic(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentStatic(void);
};
