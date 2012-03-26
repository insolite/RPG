#pragma once

class CurrentCharacter :
	public CurrentMapObject<Character>
{
public:
	char* login;
	char* password;

	__declspec(dllexport) CurrentCharacter(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentCharacter(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentCharacter(void);
};
