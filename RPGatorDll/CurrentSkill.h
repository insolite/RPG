#pragma once

class CurrentSkill :
	public CurrentGameObject<Skill>
{
public:
	CurrentCharacter* owner;

	__declspec(dllexport) CurrentSkill(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	__declspec(dllexport) CurrentSkill(char* currentSkillInfoPacket);
	__declspec(dllexport) ~CurrentSkill(void);
};
