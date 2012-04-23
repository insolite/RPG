#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Quest.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentCharacter.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentQuest.h"

//Initialization from DB (Editor, Server)
CurrentQuest::CurrentQuest(SqliteResult sqliteResult, CurrentCharacter* currentCharacter) :
	CurrentGameObject<Quest>::CurrentGameObject(sqliteResult, Game::instance->resources->quests, Game::instance->resources->questsCount)
{
	owner = currentCharacter;
	state = sqliteResult.integers["state"];
}

//Initialization from incoming packet (Client)
CurrentQuest::CurrentQuest(char* currentQuestInfoPacket) :
	CurrentGameObject<Quest>::CurrentGameObject(currentQuestInfoPacket, Game::instance->resources->quests, Game::instance->resources->questsCount)
{
	owner = NULL; //Client does not use it. It uses Universe->currentCharacter
	state = PacketGetInt(currentQuestInfoPacket, 9);
}

CurrentQuest::~CurrentQuest(void)
{
}

void CurrentQuest::Update()
{
	char sql[256];
	sprintf(sql, "UPDATE CurrentQuest SET currentCharacterId=%d, `state`=%d WHERE id=%d;", owner->id, state, id);
	sqlite3_exec(Game::instance->db, sql, NULL, NULL, NULL);
}
