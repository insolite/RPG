#pragma once

class __declspec(dllexport) CurrentSkill :
	public CurrentGameObject<Skill>
{
public:
	CurrentCharacter* owner;

	int lastUse;
	void Update();

	CurrentSkill(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	CurrentSkill(char* currentSkillInfoPacket);
	~CurrentSkill(void);
};
