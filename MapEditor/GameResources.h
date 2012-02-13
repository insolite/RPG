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
	
	int mapCellsCount;
	int npcsCount;
	int staticsCount;
	int itemsCount;

	GameResources(void);
	~GameResources(void);

private:
	bool MapCellsInit(void);
	bool NpcsInit(void);
	bool StaticsInit(void);
	bool ItemsInit(void);
};
