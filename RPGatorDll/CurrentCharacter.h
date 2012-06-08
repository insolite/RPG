#pragma once

class __declspec(dllexport) CurrentCharacter :
	public CurrentMapObject<Character>
{
public:
	char login[64]; //Also character's name
	char password[32];
	int hp;
	CurrentItem** currentItems; //Inventory
	CurrentQuest** currentQuests; //Accepted quests
	CurrentSkill** currentSkills; //Learned skills
	int currentItemsCount;
	int currentQuestsCount;
	int currentSkillsCount;
	ConnectSocket* connectSocket;

	f32 movingX; //target point
	f32 movingY; //target point
	//deltaX^2 + deltaY^2 == base->speed^2
	f32 deltaX;
	f32 deltaY;

	CurrentItem* GetItem(int id);
	CurrentItem* GetItemByBase(int id);
	CurrentQuest* GetQuest(int id);
	CurrentQuest* GetQuestByBase(int id);
	CurrentSkill* GetSkill(int id);
	CurrentSkill* GetSkillByBase(int id);
	
	void SpawnItem(CurrentItem* currentItem);
	void SpawnSkill(CurrentSkill* currentSkill);
	
	CurrentItem* AddItem(Item* base, int count);
	CurrentSkill* AddSkill(Skill* base);
	
	void Update();
	
	void RecalculateDelta();
	
	CurrentCharacter(SqliteResult sqliteResult, Location* location);
	CurrentCharacter(char* currentMapObjectSpawnedPacket);
	~CurrentCharacter(void);
};
