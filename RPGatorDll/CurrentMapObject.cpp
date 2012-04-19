#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "MapObject.h"
#include "NPC.h"
#include "Static.h"
#include "Item.h"
#include "Character.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"

template class __declspec(dllexport) CurrentMapObject<NPC>;
template class __declspec(dllexport) CurrentMapObject<Static>;
template class __declspec(dllexport) CurrentMapObject<Item>;
template class __declspec(dllexport) CurrentMapObject<Character>;

template<class T>
CurrentMapObject<T>::CurrentMapObject( SqliteResult sqliteResult, T** mapObjects, int mapObjectsCount, Location* location ) :
CurrentGameObject<T>::CurrentGameObject(sqliteResult, mapObjects, mapObjectsCount)
{
	x = sqliteResult.integers["x"];
	y = sqliteResult.integers["y"];
	currentLocation = location;
	if (base->mesh)
	{
		node = Render::instance->createNode(false, base->mesh, base->texture, false, vector3df(0.2, 0.2, 0.2), vector3df((f32)x * CELL_SIZE, 0.0f, (f32)y * CELL_SIZE));
	}
	else
		node = NULL;
	title = NULL;
}

template<class T>
CurrentMapObject<T>::CurrentMapObject( char* currentMapObjectSpawnedPacket, T** mapObjects, int mapObjectsCount ) :
CurrentGameObject<T>::CurrentGameObject(currentMapObjectSpawnedPacket, mapObjects, mapObjectsCount)
{
	x = PacketGetInt(currentMapObjectSpawnedPacket, 9);
	y = PacketGetInt(currentMapObjectSpawnedPacket, 13);
	currentLocation = NULL; //Client does not use it. It uses Universe->currentLocation
	if (base->mesh)
	{
		node = Render::instance->createNode(false, base->mesh, base->texture, false, vector3df(0.2, 0.2, 0.2), vector3df((f32)x * CELL_SIZE, 0.0f, (f32)y * CELL_SIZE));
	}
	else
		node = NULL;
	title = NULL;
}

template<class T>
CurrentMapObject<T>::~CurrentMapObject( void )
{
	if (node)
		node->remove();
	if (title)
		title->remove();
}

template<class T>
void CurrentMapObject<T>::setTitle( char* text )
{
	if (title)
		title->remove();
	wchar_t wstr[256];
	mbstowcs(wstr, text, 255);
	IBillboardTextSceneNode* title = Render::instance->smgr->addBillboardTextSceneNode(Render::instance->device->getGUIEnvironment()->getSkin()->getFont(), wstr, node, dimension2df(strlen(text) / 1.5f,1.5f), vector3df(0,60,0));
}

template<class T>
void CurrentMapObject<T>::setAnimation( EMD2_ANIMATION_TYPE animationType )
{
	if (node)
	{
		((IAnimatedMeshSceneNode*)node)->removeAnimators();
		((IAnimatedMeshSceneNode*)node)->setMD2Animation(animationType);
	}
}
