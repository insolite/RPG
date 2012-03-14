#pragma once
#include "MapCell.h"
#include "Npc.h"
#include "Static.h"
#include "Item.h"
#include "Player.h"

class GameResources
{
public:
	MapCell** mapCells;
	NPC** npcs;
	Static** statics;
	Item** items;
	//Player** players;
	sqlite3* db;
	
	int mapCellsCount;
	int npcsCount;
	int staticsCount;
	int itemsCount;

	GameResources(void);
	~GameResources(void);

private:
	template<class T>
	void MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName);
	/*
	bool MapCellsInit(void);
	bool NpcsInit(void);
	bool StaticsInit(void);
	bool ItemsInit(void);
	*/
};
