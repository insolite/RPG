#pragma once

class __declspec(dllexport) CurrentStatic :
	public CurrentMapObject<Static>
{
public:
	void Update();

	CurrentStatic(SqliteResult sqliteResult, Location* location);
	CurrentStatic(char* currentMapObjectSpawnedPacket);
	~CurrentStatic(void);
};
