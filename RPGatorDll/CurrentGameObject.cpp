#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentNPC.h"
#include "CurrentStatic.h"
#include "CurrentItem.h"
#include "CurrentCharacter.h"
#include "CurrentQuest.h"
#include "CurrentSkill.h"
#include "GameData.h"
#include "GameObject.h"
#include "MapObject.h"
#include "NPC.h"
#include "Static.h"
#include "Item.h"
#include "Character.h"
#include "Quest.h"
#include "Skill.h"
#include "GameResources.h"
#include "Game.h"
#include "CurrentGameObject.h"

template class __declspec(dllexport) CurrentGameObject<NPC>;
template class __declspec(dllexport) CurrentGameObject<Static>;
template class __declspec(dllexport) CurrentGameObject<Item>;
template class __declspec(dllexport) CurrentGameObject<Character>;
template class __declspec(dllexport) CurrentGameObject<Skill>;
template class __declspec(dllexport) CurrentGameObject<Quest>;

template class __declspec(dllexport) CurrentGameObject<MapObject>;
template class __declspec(dllexport) CurrentGameObject<GameObject>;

template<class T>
CurrentGameObject<T>::CurrentGameObject( SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount )
{
	id = sqliteResult.integers["id"];
	base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, sqliteResult.integers["baseId"]);
}

template<class T>
CurrentGameObject<T>::CurrentGameObject( char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount )
{
	id = PacketGetInt(currentMapObjectSpawnedPacket, 1);
	base = Game::instance->resources->GetMapObject<T>(mapObjects, mapObjectsCount, PacketGetInt(currentMapObjectSpawnedPacket, 5));
}

template<class T>
CurrentGameObject<T>::~CurrentGameObject( void )
{
}
