#pragma once

class CurrentItem :
	public CurrentMapObject<Item>
{
public:
	__declspec(dllexport) CurrentItem(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentItem(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentItem(void);
};
