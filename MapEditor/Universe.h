#include "Location.h"
#include "Npc.h"
#include "Player.h"
#include "Item.h"
#include "MapObject.h"
#pragma once
using namespace std;

class Universe
{
public:
	Location* currentLocation;
	Location** locations;
	vector<Npc*> npcs;
	vector<Player*> players;
	vector<Item*> items;
	vector<MapObject*> mapObjects;
	int cameraX, cameraY;

	void DDraw(Location* location, int cursorX, int cursorY);

	bool GraphicsInit();
	void SelectLocation(Location* location);
	void LocationsInit();
	void DrawScene();
	void Run();
	void CameraMove(int x, int y);
	
	Universe(void);
	~Universe(void);
};
