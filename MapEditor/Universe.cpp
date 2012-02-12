#include "StdAfx.h"
#include "Universe.h"
#include "MenuButton.h"
#include "StringListModel.h"
#include "FloorDropDown.h"
#include "LocationDropDown.h"
#include "BrushDropDown.h"
#include "NPCSelectButton.h"
#include "MapObjectSelectWindow.h"
#include "utilities.h"

Universe::Universe(void)
{
	screenWidth = 800;
	screenHeight = 600;
	cellSize = 64;
	//currentBrush = CellProperty::Free;
	//currentCellProperty = CellProperty::Locked;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
	gameName = new (char[32]);
	sprintf(gameName, "testgame");
	instance = this;
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

void Universe::CameraReset()
{
	cameraX = 0;
	cameraY = 0;
}
void Universe::CursorReset()
{
	cursorX = 0;
	cursorY = 0;
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

	LoadTexture();
	//glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenWidth, screenHeight, 0);
	//glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);

	

	glMatrixMode(GL_MODELVIEW);
	


	return false;
}

bool Universe::GUIInit(gcn::SDLInput* &GUIInput)
{
	char fontCharacters[256];
	FILE* f;

	//Input init
	GUIInput = new gcn::SDLInput();

	//Edit area container init
	editAreaContainer = new gcn::Container();
	editAreaContainer->setDimension(gcn::Rectangle(0, 0, screenWidth - toolbarWidth, screenHeight));
	editAreaContainer->setOpaque(false);
	editAreaContainer->setFocusable(true);

	//Toolbar container init
	gcn::Container* toolbarContainer = new gcn::Container();
	//toolbarContainer->setBaseColor(gcn::Color(0x7f7f7f));
	toolbarContainer->setDimension(gcn::Rectangle(0, 0, toolbarWidth, screenHeight));
	toolbarContainer->setFocusable(true);
	
	//Main container init
	gcn::Container* mainContainer = new gcn::Container();
	mainContainer->setDimension(gcn::Rectangle(0, 0, screenWidth, screenHeight));
	mainContainer->setOpaque(false);
	mainContainer->add(editAreaContainer, 0, 0);
	mainContainer->add(toolbarContainer, screenWidth - toolbarWidth, 0);
	
	//GUI init
	toolbar = new gcn::Gui();
	toolbar->setGraphics(new gcn::OpenGLGraphics(screenWidth, screenHeight));
	toolbar->setInput(GUIInput);
	toolbar->setTop(mainContainer);

	//Font init
	f = fopen("editor/_font/char.txt", "rt");
	if (!f)
		return true;
	fgets(fontCharacters, 256, f);
	fclose(f);
	gcn::Image::setImageLoader(new gcn::OpenGLSDLImageLoader());
	gcn::ImageFont* mFontWhite = new gcn::ImageFont("editor/_font/face.png", fontCharacters);
	gcn::Widget::setGlobalFont(mFontWhite);

	//GUI building

	//Floor control DropDown
	FloorDropDown* floorsDropDown = new FloorDropDown(this);
	floorsDropDown->add("outside");
	floorsDropDown->add("first fl.");
	floorsDropDown->setSelected(0);
	toolbarContainer->add(floorsDropDown, toolbarLeftMargin, 32);

	//Location control DropDown
	LocationDropDown* locationsDropDown = new LocationDropDown(this);
	for (int i = 0; i < locationsCount; i++)
		locationsDropDown->add(locations[i]->name);
	locationsDropDown->setSelected(0);
	toolbarContainer->add(locationsDropDown, toolbarLeftMargin, 56);

	//Brush selection
	BrushDropDown* brushesDropDown = new BrushDropDown(this);
	char str[16];
	for (int i = 0; i < brushesCount; i++)
	{
		sprintf(str, "%dx", brushMasks[i]->width);
		brushesDropDown->add(str);
	}
	brushesDropDown->setSelected(0);
	toolbarContainer->add(brushesDropDown, toolbarLeftMargin, 80);
	
	//NPC select button
	NPCSelectButton* npcSelectButton = new NPCSelectButton("NPC");
	toolbarContainer->add(npcSelectButton, toolbarLeftMargin, 104);

	//Test NPCs creating
	NPC** npcs = new NPC*[5];
	npcs[0] = new NPC();
	npcs[1] = new NPC();
	npcs[2] = new NPC();
	npcs[3] = new NPC();
	npcs[4] = new NPC();
	npcs[0]->name = new char[64];
	npcs[1]->name = new char[64];
	npcs[2]->name = new char[64];
	npcs[3]->name = new char[64];
	npcs[4]->name = new char[64];
	strcpy(npcs[0]->name, "Gremlin");
	strcpy(npcs[1]->name, "Monster Eye Destroyer");
	strcpy(npcs[2]->name, "Doom Knight");
	strcpy(npcs[3]->name, "Really very very very looong name");
	strcpy(npcs[4]->name, "Doom Knight");
	npcs[0]->tags = new char*[1];
	npcs[1]->tags = new char*[1];
	npcs[2]->tags = new char*[1];
	npcs[3]->tags = new char*[1];
	npcs[4]->tags = new char*[1];
	npcs[0]->tags[0] = new char[64];
	npcs[1]->tags[0] = new char[64];
	npcs[2]->tags[0] = new char[64];
	npcs[3]->tags[0] = new char[64];
	npcs[4]->tags[0] = new char[64];
	strcpy(npcs[0]->tags[0], "Humans");
	strcpy(npcs[1]->tags[0], "Elves");
	strcpy(npcs[2]->tags[0], "Orcs");
	strcpy(npcs[3]->tags[0], "Humans");
	strcpy(npcs[4]->tags[0], "Orcs");
	npcs[0]->tagsCount = 1;
	npcs[1]->tagsCount = 1;
	npcs[2]->tagsCount = 1;
	npcs[3]->tagsCount = 1;
	npcs[4]->tagsCount = 1;
	//NPC select window
	npcSelectWindow = new MapObjectSelectWindow("NPC selection", (MapObject**)npcs, 5); //TODO: explicit convertion? Really? o_0
	mainContainer->add(npcSelectWindow);
	
	/*
	gcn::TabbedArea* npcTabbedArea = new gcn::TabbedArea();
	npcTabbedArea->setSize(200, 100);
	gcn::Button* tabOneButton = new gcn::Button("Button 1");
	npcTabbedArea->addTab("Tab 1", tabOneButton);
	gcn::Button* tabTwoButton = new gcn::Button("Button 2");
	npcTabbedArea->addTab("Tab 2", tabTwoButton);
	//window->add(npcTabbedArea);
	*/

	gcn::RadioButton* brushTypeRadioButton1 = new gcn::RadioButton("Typ", "Brush", true);
	gcn::RadioButton* brushTypeRadioButton2 = new gcn::RadioButton("Tex", "Brush", false);
	gcn::RadioButton* brushTypeRadioButton3 = new gcn::RadioButton("Npc", "Brush", false);
	gcn::RadioButton* brushTypeRadioButton4 = new gcn::RadioButton("Obj", "Brush", false);
	toolbarContainer->add(brushTypeRadioButton1, toolbarLeftMargin, 132);
	toolbarContainer->add(brushTypeRadioButton2, toolbarLeftMargin, 148);
	toolbarContainer->add(brushTypeRadioButton3, toolbarLeftMargin, 164);
	toolbarContainer->add(brushTypeRadioButton4, toolbarLeftMargin, 180);

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
	
	//glBegin(GL_QUADS);
	for (i = 0; i < currentLocation->height; i++)
	{
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j]->cellProperty)
			{
			case CellProperty::Free:
				glColor4d(0, 1, 0, 1);
				break;
			case CellProperty::Locked:
				glColor4d(1, 0, 0, 0.5);
				break;
			default:
				glColor4d(1, 1, 1, 1);
			}
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize + cellSize);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize + cellSize);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize);
			glEnd();

		}
	}
	//glEnd();

	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		for (i = 0; i < currentBrushMask->width; i++)
		{
			for (j = 0; j < currentBrushMask->width; j++)
			{
				if (currentBrushMask->mask[i][j])
				{
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j), Index2Pix(cursorY - currentBrushMask->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrushMask->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrushMask->width/2 + i) + cellSize);
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j), Index2Pix(cursorY - currentBrushMask->width/2 + i) + cellSize);
				}
			}
		}
	glEnd();

	toolbar->draw();

	//glFlush();
	SDL_GL_SwapBuffers();
}

void Universe::SetLocation(Location* location)
{
	CameraReset();
	CursorReset();
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

	CameraReset();
	CursorReset();

	GraphicsInit();
	GUIInit(GUIInput);

	//TESTTESTTESTTESTTESTTEST
	LoadTexture();

	mouseX = 0;
	mouseY = 0;

	continueFlag = true;
	
	keys = SDL_GetKeyState(NULL);
	int lastUpdate = SDL_GetTicks();

	while (continueFlag)
	{
		SDL_PumpEvents();
		
		while (SDL_PollEvent(&event))
		{
			GUIInput->pushInput(event); //((gcn::SDLInput*)(toolbar->getInput()))->pushInput(event); //This code doing the same without defined pointer to GUIInput, but looks too bad...
			toolbar->logic();
		}

		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1))
		{
			//if (mouseX < (screenWidth - toolbarWidth)) //Prevents drawing cells with brush while mouse cursor is on the toolbar
			if (editAreaContainer->isFocused())
				Paint();
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
			/*
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			*/
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
		
		if ((SDL_GetTicks() - lastUpdate) > 40) //14 for 60fps, 22 for 41fps, 40 for 24fps
		{
			DrawScene();
			lastUpdate = SDL_GetTicks();
		}
		Sleep(1);
	}
}

bool Universe::BrushesInit()
{
	int i, j, k, count;
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
	brushMasks = new BrushMask*[count];
	for (k = 0; k < count; k++)
	{
		brushMasks[k] = new BrushMask();
		brushMasks[k]->Init(fgetc(f));
		for (i = 0; i < brushMasks[k]->width; i++)
			for (j = 0; j < brushMasks[k]->width; j++)
				brushMasks[k]->mask[i][j] = fgetc(f) ? true : false; //the same as fgetc(f), but VC warnings...
	}
	fclose(f);
	brushesCount = count;
	currentBrushMask = brushMasks[0];

	brush[0] = new MapCell(); //game->mapCells[0]->type; //type ~ cellProperty
	brush[1] = new NPC();
	brush[2] = new Static();
	brush[3] = new Item();
	brushIndex = 0;

	//Test
	((MapCell*)brush[0])->cellProperty = CellProperty::Locked;

	return false;
}

void Universe::Paint()
{
	int i, j;

	for (i = 0; i < currentBrushMask->width; i++)
		for (j = 0; j < currentBrushMask->width; j++)
			if ((cursorX - currentBrushMask->width/2 + j) >= 0 && 
				(cursorY - currentBrushMask->width/2 + i) >= 0 && 
				(cursorX - currentBrushMask->width/2 + j) < currentLocation->width && 
				(cursorY - currentBrushMask->width/2 + i) < currentLocation->height && 
				currentBrushMask->mask[i][j]
				)
				currentLocation->mask[cursorY - currentBrushMask->width/2 + i][cursorX - currentBrushMask->width/2 + j]->cellProperty = ((MapCell*)brush[brushIndex])->cellProperty;
}

bool Universe::LoadTexture()
{
	// Picture loading
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("grass.bmp");

	// Texture creating
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	return true;
}
