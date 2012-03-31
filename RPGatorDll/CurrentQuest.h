#pragma once

class CurrentQuest :
	public CurrentGameObject<Quest>
{
public:
	CurrentCharacter* owner;
	int state;

	__declspec(dllexport) CurrentQuest(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	__declspec(dllexport) CurrentQuest(char* currentQuestInfoPacket);
	__declspec(dllexport) ~CurrentQuest(void);
};
