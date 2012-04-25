#pragma once

class CurrentSkill :
	public CurrentGameObject<Skill>
{
public:
	CurrentCharacter* owner;

	u32 lastUse;

	__declspec(dllexport) CurrentSkill(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	__declspec(dllexport) CurrentSkill(char* currentSkillInfoPacket);
	__declspec(dllexport) ~CurrentSkill(void);
};
