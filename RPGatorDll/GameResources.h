#pragma once
#include "MapCell.h"
#include "NPC.h"
#include "Static.h"
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

	__declspec(dllexport) GameResources(void);
	__declspec(dllexport) ~GameResources(void);

private:
	template<class T>
	__declspec(dllexport) void MapObjectsInit(T** &mapObjects, int &mapObjectsCount, char* tableName);
	/*
	bool MapCellsInit(void);
	bool NpcsInit(void);
	bool StaticsInit(void);
	bool ItemsInit(void);
	*/
};
