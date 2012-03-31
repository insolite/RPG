#pragma once

class CurrentCharacter :
	public CurrentMapObject<Character>
{
public:
	char* login; //Also character's name
	char* password;
	CurrentItem** currentItems; //Inventory
	CurrentQuest** currentQuests; //Accepted quests
	CurrentSkill** currentSkills; //Learned skills
	int currentItemsCount;
	int currentQuestsCount;
	int currentSkillsCount;

	__declspec(dllexport) CurrentCharacter(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentCharacter(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentCharacter(void);
};
