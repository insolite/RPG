#pragma once
#include "Location.h"
#include "Npc.h"
#include "Player.h"
#include "Item.h"
#include "MapObject.h"
#include "CursorBrush.h"
using namespace std;

class Universe
{
public:
	static Universe* instance;
	Location* currentLocation;
	Location** locations;
	vector<NPC*> npcs;
	vector<Player*> players;
	vector<Item*> items;
	vector<MapObject*> mapObjects;
	int cameraX, cameraY; //pixels
	int cursorX, cursorY; //points
	int screenWidth, screenHeight; //pixels
	int toolbarWidth; //pixels
	int toolbarLeftMargin; //pixels
	int cellSize; //pixels
	int locationsCount;

	GLuint texture[1];

	CellProperty currentCellProperty;
	CursorBrush** brushes;
	CursorBrush* currentBrush;
	int brushesCount;
	char* gameName;

	//GUI
	gcn::Gui* toolbar;
	gcn::Container* editAreaContainer;
	gcn::Window* npcSelectWindow;
	
	bool LoadTexture();
	bool GraphicsInit();
	bool GUIInit(gcn::SDLInput* &GUIInput);
	bool BrushesInit();
	bool LocationsInit();
	void SetLocation(Location* location);
	void DrawScene();
	void Run();
	void CameraMove(int x, int y);
	void CameraReset();
	void CursorReset();
	void Paint();
	

	int Pix2Index(int pos);
	int Index2Pix(int pos);
	int PixRound(int pos);
	
	Universe(void);
	~Universe(void);


};
