#pragma once
#include "Location.h"
#include "Npc.h"
#include "Static.h"
#include "Player.h"
#include "Item.h"
#include "MapObject.h"
#include "BrushMask.h"
#include "StringListModel.h"
#include "MapObjectSelectTabContainer.h"
#include "MapObjectSelectWindow.h"
#include "FloorDropDown.h"
#include "LocationDropDown.h"
#include "BrushDropDown.h"
#include "ToggleWindowVisibilityButton.h"
#include "FocusingWindow.h"
#include "Game.h"
#include "utilities.h"
using namespace std;

class Universe
{
public:
	static Universe* instance;
	Location* currentLocation;
	Game* game;
	int cameraX, cameraY; //pixels
	int cursorX, cursorY; //points
	int screenWidth, screenHeight; //pixels
	bool fullscreen;
	int toolbarWidth; //pixels
	int toolbarLeftMargin; //pixels
	int cellSize; //pixels

	GLuint texture[1];

	//CellProperty currentCellProperty;
	BrushMask** brushMasks;
	BrushMask* currentBrushMask;
	int brushesCount;

	MapObject* brush[4];
	int brushIndex; //TODO: char

	//GUI
	gcn::Gui* toolbar;
	gcn::Container* editAreaContainer;
	gcn::Window* mapCellSelectWindow;
	gcn::Window* npcSelectWindow;
	gcn::Window* staticSelectWindow;
	gcn::Window* itemSelectWindow;

	gcn::Slider* brushMaskSlider;
	gcn::Label* brushMaskSizeLabel;
	StringDropDown* brushesDropDown;

	gcn::Container* mapCellSelectTabContainer;
	gcn::Container* npcSelectTabContainer;
	gcn::Container* staticSelectTabContainer;
	gcn::Container* itemSelectTabContainer;

	bool LoadTexture();
	bool GraphicsInit();
	bool GUIInit(gcn::SDLInput* &GUIInput);
	bool BrushesInit();
	void SetLocation(Location* location);
	void DrawScene();
	void Run();
	void CameraMove(int x, int y);
	void CameraReset();
	void CursorReset();
	void PaintMapCell();
	
	int Pix2Index(int pos);
	int Index2Pix(int pos);
	int PixRound(int pos);
	
	Universe(void);
	~Universe(void);
};
