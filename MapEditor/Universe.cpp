#include "StdAfx.h"
#include "Universe.h"
#include "MenuButton.h"
#include "FloorListModel.h"
#include "NPCListModel.h"
#include "BrushListModel.h"
#include "LocationListModel.h"
#include "DropDownActionListener.h"
#include "utilities.h"

Universe::Universe(void)
{
	cameraX = 0;
	cameraY = 0;
	screenWidth = 800;
	screenHeight = 600;
	cellSize = 64;
	//currentBrush = CellProperty::Free;
	currentCellProperty = CellProperty::Locked;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
	gameName = new (char[32]);
	sprintf(gameName, "testgame");
}

Universe::~Universe(void)
{
}

int Universe::Pix2Index(int pos)
{
	return pos / cellSize;
}

int Universe::Index2Pix(int pos)
{
	return pos * cellSize;
}

int Universe::PixRound(int pos)
{
	return Index2Pix(Pix2Index(pos));
}

bool Universe::GraphicsInit()
{
	bool FULLSCREEN;

	Uint32 flags = SDL_OPENGL;
	
	FULLSCREEN = false;
	
	if (FULLSCREEN)
		flags |= SDL_FULLSCREEN;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return true;
	}
	SDL_WM_SetCaption("RPG", NULL);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
 
	SDL_SetVideoMode(screenWidth, screenHeight, 32, flags);

	//glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, screenHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);

	return false;
}

bool Universe::GUIInit(gcn::SDLInput* &GUIInput)
{
	char* fontCharacters;
	char* path;
	FILE* f;

	//Input init
	GUIInput = new gcn::SDLInput();

	//Container init
	gcn::Container* toolbarContainer = new gcn::Container();
	toolbarContainer->setBaseColor(gcn::Color(0x7f7f7f));
	toolbarContainer->setDimension(gcn::Rectangle(screenWidth - toolbarWidth, 0, toolbarWidth, screenHeight));

	//GUI init
	toolbar = new gcn::Gui();
	toolbar->setGraphics(new gcn::OpenGLGraphics(screenWidth, screenHeight));
	toolbar->setInput(GUIInput);
	toolbar->setTop(toolbarContainer);

	//Font init
	//TODO: For map editor interface we have to load some 'system' font, not in-game font
	path = new (char[256]);
	sprintf(path, "game/%s/resource/interface/font/char.txt", gameName);
	f = fopen(path, "rt");
	if (!f)
	{
		delete path;
		return true;
	}
	fontCharacters = new (char[256]);
	fgets(fontCharacters, 256, f);
	fclose(f);
	sprintf(path, "game/%s/resource/interface/font/face.png", gameName);
	gcn::Image::setImageLoader(new gcn::OpenGLSDLImageLoader());
	gcn::ImageFont* mFontWhite = new gcn::ImageFont(path, fontCharacters);
	gcn::Widget::setGlobalFont(mFontWhite);
	delete path;
	delete fontCharacters;

	//GUI building
	MenuButton* testButton = new MenuButton("Test");
	toolbarContainer->add(testButton, 64, 128);

	DropDownActionListener* dropDownActionListener = new DropDownActionListener(this);
	
	FloorListModel* floorListModel = new FloorListModel();
	gcn::DropDown* floorsDropDown = new gcn::DropDown(floorListModel);
	floorsDropDown->setSelected(0);
	toolbarContainer->add(floorsDropDown, toolbarLeftMargin, 8);
	floorsDropDown->setFocusable(false);

	BrushListModel* brushListModel = new BrushListModel(brushes, brushesCount);
	gcn::DropDown* brushesDropDown = new gcn::DropDown(brushListModel);
	brushesDropDown->setSelected(0);
	toolbarContainer->add(brushesDropDown, toolbarLeftMargin, 32);
	brushesDropDown->setFocusable(false);
	brushesDropDown->addActionListener(dropDownActionListener);
	dropDownActionListener->brushesDropDown = brushesDropDown;
	
	LocationListModel* locationListModel = new LocationListModel(locations, locationsCount);
	gcn::DropDown* locationsDropDown = new gcn::DropDown(locationListModel);
	locationsDropDown->setSelected(0);
	toolbarContainer->add(locationsDropDown, toolbarLeftMargin, 56);
	locationsDropDown->setFocusable(false);
	locationsDropDown->addActionListener(dropDownActionListener);
	dropDownActionListener->locationsDropDown = locationsDropDown;

	gcn::RadioButton* brushTypeRadioButton1 = new gcn::RadioButton("Typ", "Brush", true);
	gcn::RadioButton* brushTypeRadioButton2 = new gcn::RadioButton("Tex", "Brush", false);
	gcn::RadioButton* brushTypeRadioButton3 = new gcn::RadioButton("Npc", "Brush", false);
	gcn::RadioButton* brushTypeRadioButton4 = new gcn::RadioButton("Obj", "Brush", false);
	toolbarContainer->add(brushTypeRadioButton1, toolbarLeftMargin, 132);
	toolbarContainer->add(brushTypeRadioButton2, toolbarLeftMargin, 148);
	toolbarContainer->add(brushTypeRadioButton3, toolbarLeftMargin, 164);
	toolbarContainer->add(brushTypeRadioButton4, toolbarLeftMargin, 180);

	/*
	NPCListModel* npcListModel = new NPCListModel();
	gcn::ListBox* listBox = new gcn::ListBox(npcListModel);
	gcn::ScrollArea* sa = new gcn::ScrollArea();
	sa->setVerticalScrollPolicy(gcn::ScrollArea::SHOW_ALWAYS);
	sa->setContent(listBox);
	toolbarContainer->add(listBox, 8, 256);
	//toolbarContainer->add(sa, 8, 300);
	*/

	return false;
}

bool Universe::LocationsInit()
{
	char locationsPath[256];
	char **folders;
	int id, i;

	sprintf(locationsPath, "game/%s/location", gameName);
	locationsCount = ReadDir(locationsPath, folders, true);
	locations = new (Location*[locationsCount]);
	for (i = 0; i < locationsCount; i++)
	{
		sscanf(folders[i], "%d", &id);
		delete folders[i];
		locations[i] = new Location();
		if (locations[i]->Init(gameName, id)) //LocationsInit fails if at least one location failed to load
		{
			for (int j = 0; j <= i; j++)
				delete locations[i];
			delete locations;
			delete folders;
			return true;
		}
	}
	delete folders;
	SetLocation(locations[0]);
	return false;
}

void Universe::CameraMove(int x, int y)
{
	if ((cameraX + x) < 0 || ((cameraX + x) + screenWidth - toolbarWidth) >= currentLocation->width * cellSize)
		x = 0;
	if ((cameraY + y) < 0 || ((cameraY + y) + screenHeight) >= currentLocation->height * cellSize)
		y = 0;
	cameraX += x;
	cameraY += y;
	//Sleep(8);
}

void Universe::DrawScene()
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(-cameraX, -cameraY, 0); //Camera positioning
	
	glBegin(GL_QUADS);
	for (i = 0; i < currentLocation->height; i++)
	{
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j].cellProperty)
			{
			case CellProperty::Free:
				glColor3d(0, 1, 0);
				break;
			case CellProperty::Locked:
				glColor3d(1, 0, 0);
				break;
			default:
				glColor3d(1, 1, 1);
			}
			glVertex2d(j * cellSize, i * cellSize);
			glVertex2d(j * cellSize, i * cellSize + cellSize);
			glVertex2d(j * cellSize + cellSize, i * cellSize + cellSize);
			glVertex2d(j * cellSize + cellSize, i * cellSize);
		}
	}
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		for (i = 0; i < currentBrush->width; i++)
		{
			for (j = 0; j < currentBrush->width; j++)
			{
				if (currentBrush->mask[i][j])
				{
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + j), Index2Pix(cursorY - currentBrush->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrush->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrush->width/2 + i) + cellSize);
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + j), Index2Pix(cursorY - currentBrush->width/2 + i) + cellSize);
				}
			}
		}
	glEnd();

	toolbar->draw();

	glFlush();
	SDL_GL_SwapBuffers();
}

void Universe::SetLocation(Location* location)
{
	cameraX = 0;
	cameraY = 0;
	cursorX = 0;
	cursorY = 0;
	currentLocation = location;
}

void Universe::Run()
{
	Uint8 *keys;
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	int mouseX, mouseY;
	bool continueFlag;

	LocationsInit();
	BrushesInit();

	GraphicsInit();
	GUIInit(GUIInput);
	
	mouseX = 0;
	mouseY = 0;

	continueFlag = true;
	
	keys = SDL_GetKeyState(NULL);

	while (continueFlag)
	{
		SDL_PumpEvents();
		
		while (SDL_PollEvent(&event))
		{
			GUIInput->pushInput(event); //((gcn::SDLInput*)(toolbar->getInput()))->pushInput(event); //This code doing the same without defined pointer to GUIInput, but looks too bad...
			toolbar->logic();
		}

		//TODO: Put this inside the switch below
		//EXIT
		if (keys[SDLK_ESCAPE])
		{
			continueFlag = false;
		}
		//CAMERA UP LEFT
		else if (keys[SDLK_UP] && keys[SDLK_LEFT])
		{
			CameraMove(-1, -1);
		}
		//CAMERA UP RIGHT
		else if (keys[SDLK_UP] && keys[SDLK_RIGHT])
		{
			CameraMove(1, -1);
		}
		//CAMERA DOWN LEFT
		else if (keys[SDLK_DOWN] && keys[SDLK_LEFT])
		{
			CameraMove(-1, 1);
		}
		//CAMERA DOWN RIGHT
		else if (keys[SDLK_DOWN] && keys[SDLK_RIGHT])
		{
			CameraMove(1, 1);
		}
		//CAMERA UP
		else if (keys[SDLK_UP])
		{
			CameraMove(0, -1);
		}
		//CAMERA DOWN
		else if (keys[SDLK_DOWN])
		{
			CameraMove(0, 1);
		}
		//CAMERA LEFT
		else if (keys[SDLK_LEFT])
		{
			CameraMove(-1, 0);
		}
		//CAMERA RIGHT
		else if (keys[SDLK_RIGHT])
		{
			CameraMove(1, 0);
		}

		switch (event.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keys = SDL_GetKeyState(NULL);
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (mouseX < (screenWidth - toolbarWidth)) //Prevents drawing cells with brush while mouse cursor is on the toolbar
					Paint();
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				continueFlag = false;
				break;
			default:
				break;
		}

		if (mouseX < (screenWidth - toolbarWidth)) //Prevents cursor moving while mouse cursor is on the toolbar
		{
			cursorX = Pix2Index(mouseX + cameraX);
			cursorY = Pix2Index(mouseY + cameraY);
		}
		//printf("%d : %d\n", cursorX, cursorY);
		
		DrawScene();
	}
}

bool Universe::BrushesInit()
{
	int i, j, k, count, width;
	FILE* f;
	
	f = fopen("editor/brushes.dat", "rb");
	if (!f)
		return true;
	count = fgetc(f);
	if (!count) //No brushes found
	{
		fclose(f);
		return true;
	}
	brushes = new CursorBrush*[count];
	for (k = 0; k < count; k++)
	{
		brushes[k] = new CursorBrush();
		brushes[k]->Init(fgetc(f));
		for (i = 0; i < brushes[k]->width; i++)
			for (j = 0; j < brushes[k]->width; j++)
				brushes[k]->mask[i][j] = fgetc(f);
	}
	fclose(f);
	brushesCount = count;
	currentBrush = brushes[0];
	return false;
}

void Universe::Paint()
{
	int i, j;

	for (i = 0; i < currentBrush->width; i++)
		for (j = 0; j < currentBrush->width; j++)
			if ((cursorX - currentBrush->width/2 + j) >= 0 && 
				(cursorY - currentBrush->width/2 + i) >= 0 && 
				(cursorX - currentBrush->width/2 + j) < currentLocation->width && 
				(cursorY - currentBrush->width/2 + i) < currentLocation->height && 
				currentBrush->mask[i][j]
				)
				currentLocation->mask[cursorY - currentBrush->width/2 + i][cursorX - currentBrush->width/2 + j].cellProperty = currentCellProperty;
}
