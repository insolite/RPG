#pragma once

class CurrentItem :
	public CurrentMapObject<Item>
{
public:
	CurrentCharacter* owner;

	__declspec(dllexport) CurrentItem(SqliteResult sqliteResult, Location* location, CurrentCharacter* currentCharacter = NULL);
	__declspec(dllexport) CurrentItem(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentItem(void);
};
