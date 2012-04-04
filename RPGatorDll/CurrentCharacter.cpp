#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "Character.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentItem.h"
#include "CurrentQuest.h"
#include "CurrentSkill.h"
#include "GameResources.h"
#include "Game.h"
#include "../Include/RPGator/ConnectSocket.h"
#include "CurrentCharacter.h"

//Initialization from DB (Editor, Server)
CurrentCharacter::CurrentCharacter(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<Character>::CurrentMapObject(sqliteResult, Game::instance->resources->characters, Game::instance->resources->charactersCount, location)
{
	login = new char[sqliteResult.strings["login"].length() + 1];
	strcpy(login, sqliteResult.strings["login"].c_str());
	password = new char[sqliteResult.strings["password"].length() + 1];
	strcpy(password, sqliteResult.strings["password"].c_str());

	char query[256];
	int rowsCount;
	std::vector<SqliteResult> sqliteResultsChildren;

	//CurrentItems
	sprintf(query, "SELECT * FROM CurrentItem WHERE locationId=0 AND currentCharacterId=%d", id);
	sqliteResultsChildren = SqliteGetRows(Game::instance->db, query);
	currentItems = NULL;
	currentItemsCount = 0;
	rowsCount = sqliteResultsChildren.size();
	while (currentItemsCount < rowsCount)
	{
		currentItemsCount++;
		currentItems = (CurrentItem**)realloc(currentItems, currentItemsCount * sizeof(CurrentItem*));
		currentItems[currentItemsCount - 1] = new CurrentItem(sqliteResultsChildren[currentItemsCount - 1], NULL, this);
	}

	//CurrentQuests
	sprintf(query, "SELECT * FROM CurrentQuest WHERE currentCharacterId=%d", id);
	sqliteResultsChildren = SqliteGetRows(Game::instance->db, query);
	currentQuests = NULL;
	currentQuestsCount = 0;
	rowsCount = sqliteResultsChildren.size();
	while (currentQuestsCount < rowsCount)
	{
		currentQuestsCount++;
		currentQuests = (CurrentQuest**)realloc(currentQuests, currentQuestsCount * sizeof(CurrentQuest*));
		currentQuests[currentQuestsCount - 1] = new CurrentQuest(sqliteResultsChildren[currentQuestsCount - 1], this);
	}

	//CurrentSkills
	sprintf(query, "SELECT * FROM CurrentSkill WHERE currentCharacterId=%d", id);
	sqliteResultsChildren = SqliteGetRows(Game::instance->db, query);
	currentSkills = NULL;
	currentSkillsCount = 0;
	rowsCount = sqliteResultsChildren.size();
	while (currentSkillsCount < rowsCount)
	{
		currentSkillsCount++;
		currentSkills = (CurrentSkill**)realloc(currentSkills, currentSkillsCount * sizeof(CurrentSkill*));
		currentSkills[currentSkillsCount - 1] = new CurrentSkill(sqliteResultsChildren[currentSkillsCount - 1], this);
	}
}

//Initialization from incoming packet (Client)
CurrentCharacter::CurrentCharacter(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<Character>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->characters, Game::instance->resources->charactersCount)
{
	//type(1) + id(4) + baseId(4) + x(4) + y(4) = 17
	login = new char[strlen(currentMapObjectSpawnedPacket + 3) + 1];
	strcpy(login, PacketGetString(currentMapObjectSpawnedPacket, 17));
	password = NULL;

	currentItems = NULL;
	currentItemsCount = 0;

	currentQuests = NULL;
	currentQuestsCount = 0;

	currentSkills = NULL;
	currentSkillsCount = 0;
}

CurrentCharacter::~CurrentCharacter(void)
{
	delete login;
	if (password) //Client does not hold passwords
		delete password;
}

CurrentItem* CurrentCharacter::GetItem(int id)
{
	for (int i = 0; i < currentItemsCount; i++)
		if (currentItems[i]->id == id)
			return currentItems[i];
	return NULL;
}

CurrentQuest* CurrentCharacter::GetQuest(int id)
{
	for (int i = 0; i < currentQuestsCount; i++)
		if (currentQuests[i]->id == id)
			return currentQuests[i];
	return NULL;
}

CurrentSkill* CurrentCharacter::GetSkill(int id)
{
	for (int i = 0; i < currentSkillsCount; i++)
		if (currentSkills[i]->id == id)
			return currentSkills[i];
	return NULL;
}
