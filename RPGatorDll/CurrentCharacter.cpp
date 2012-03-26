#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "MapObject.h"
#include "Character.h"
#include "CurrentMapObject.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentCharacter.h"

//Initialization from DB (Editor, Server)
CurrentCharacter::CurrentCharacter(SqliteResult sqliteResult, Location* location) :
	CurrentMapObject<Character>::CurrentMapObject(sqliteResult, Game::instance->resources->characters, Game::instance->resources->charactersCount, location)
{
	login = new char[sqliteResult.strings["login"].length() + 1];
	strcpy(login, sqliteResult.strings["login"].c_str());
	password = new char[sqliteResult.strings["password"].length() + 1];
	strcpy(password, sqliteResult.strings["password"].c_str());
}

//Initialization from incoming packet (Client)
CurrentCharacter::CurrentCharacter(char* currentMapObjectSpawnedPacket) :
	CurrentMapObject<Character>::CurrentMapObject(currentMapObjectSpawnedPacket, Game::instance->resources->characters, Game::instance->resources->charactersCount)
{
	//type(1) + id(4) + baseId(4) + x(4) + y(4) = 17
	login = new char[strlen(currentMapObjectSpawnedPacket + 3) + 1];
	strcpy(login, PacketGetString(currentMapObjectSpawnedPacket, 17));
	password = NULL;
}

CurrentCharacter::~CurrentCharacter(void)
{
	delete login;
	if (password) //Client does not hold passwords
		delete password;
}
