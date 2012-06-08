#pragma once

class __declspec(dllexport) CurrentItem :
	public CurrentMapObject<Item>
{
public:
	CurrentCharacter* owner;
	int count;

	void Update();

	CurrentItem(SqliteResult sqliteResult, Location* location, CurrentCharacter* currentCharacter = NULL);
	CurrentItem(char* currentMapObjectSpawnedPacket);
	~CurrentItem(void);
};
