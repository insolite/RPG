#pragma once

class CurrentSkill :
	public CurrentGameObject<Skill>
{
public:
	CurrentCharacter* owner;
	char path[256]; //Predefined path. Just to know path to the scripy and do not define it each time it executes

	__declspec(dllexport) CurrentSkill(SqliteResult sqliteResult, CurrentCharacter* currentCharacter);
	__declspec(dllexport) CurrentSkill(char* currentSkillInfoPacket);
	__declspec(dllexport) ~CurrentSkill(void);
};
