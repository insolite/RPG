#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "Skill.h"
#include "CurrentGameObject.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentSkill.h"

//Initialization from DB (Editor, Server)
CurrentSkill::CurrentSkill(SqliteResult sqliteResult, CurrentCharacter* currentCharacter) :
	CurrentGameObject<Skill>::CurrentGameObject(sqliteResult, Game::instance->resources->skills, Game::instance->resources->skillsCount)
{
	this->base->useDelay = 1000;
	lastUse = 0;
	owner = currentCharacter;
}

//Initialization from incoming packet (Client)
CurrentSkill::CurrentSkill(char* currentSkillInfoPacket) :
	CurrentGameObject<Skill>::CurrentGameObject(currentSkillInfoPacket, Game::instance->resources->skills, Game::instance->resources->skillsCount)
{
	//lastUse = 0;
	owner = NULL; //Client does not use it. It uses Universe->currentCharacter
}

CurrentSkill::~CurrentSkill(void)
{
}
