#pragma once

class CurrentItem :
	public CurrentMapObject<Item>
{
public:
	CurrentCharacter* owner;
	int count;

	__declspec(dllexport) void Update();

	__declspec(dllexport) CurrentItem(SqliteResult sqliteResult, Location* location, CurrentCharacter* currentCharacter = NULL);
	__declspec(dllexport) CurrentItem(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentItem(void);
};
