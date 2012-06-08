#pragma once

class __declspec(dllexport) CurrentQuest :
	public CurrentGameObject<Quest>
{
public:
	CurrentCharacter* owner;
	int state;

	void Update();

	CurrentQuest(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	CurrentQuest(char* currentQuestInfoPacket);
	~CurrentQuest(void);
};
