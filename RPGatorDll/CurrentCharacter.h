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
	ConnectSocket* connectSocket;

	int moveDuration;
	float floatX;
	float floatY;


	int hp;

	__declspec(dllexport) CurrentItem* GetItem(int id);
	__declspec(dllexport) CurrentItem* GetItemByBase(int id);
	__declspec(dllexport) CurrentQuest* GetQuest(int id);
	__declspec(dllexport) CurrentQuest* GetQuestByBase(int id);
	__declspec(dllexport) CurrentSkill* GetSkill(int id);
	__declspec(dllexport) CurrentSkill* GetSkillByBase(int id);
	
	__declspec(dllexport) void SpawnItem(CurrentItem* currentItem);
	__declspec(dllexport) void SpawnSkill(CurrentSkill* currentSkill);
	
	__declspec(dllexport) CurrentItem* AddItem(Item* base, int count);
	__declspec(dllexport) CurrentSkill* AddSkill(Skill* base);
	
	__declspec(dllexport) CurrentCharacter(SqliteResult sqliteResult, Location* location);
	__declspec(dllexport) CurrentCharacter(char* currentMapObjectSpawnedPacket);
	__declspec(dllexport) ~CurrentCharacter(void);
};
