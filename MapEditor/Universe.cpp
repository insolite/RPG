#include "StdAfx.h"
#include "Universe.h"
#include "MenuButton.h"
#include "FloorListModel.h"
#include "NPCListModel.h"
#include "BrushListModel.h"
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
	toolbarContainer->setBaseColor(gcn::Color(0x000000));
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

	//TODO: Move it to the class definition
	int toolbarLeftMargin = 8; //pixels

	//GUI building
	MenuButton* testButton = new MenuButton("Test");
	toolbarContainer->add(testButton, 64, 64);

	FloorListModel* floorListModel = new FloorListModel();
	gcn::DropDown* floorsDropDown = new gcn::DropDown(floorListModel);
	floorsDropDown->setSelected(0);
	toolbarContainer->add(floorsDropDown, toolbarLeftMargin, 8);

	BrushesInit();

	BrushListModel* brushListModel = new BrushListModel(brushes, brushesCount);
	gcn::DropDown* brushesDropDown = new gcn::DropDown(brushListModel);
	brushesDropDown->setSelected(0);
	DropDownActionListener* brushesDropDownActionListener = new DropDownActionListener(brushesDropDown, currentBrush, brushes);
	brushesDropDown->addActionListener(brushesDropDownActionListener);
	toolbarContainer->add(brushesDropDown, toolbarLeftMargin, 32);

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
	char* path = new (char[256]);

	//TODO: Load all locations
	locationsCount = 1;
	locations = new (Location*[locationsCount]);
	for (int i = 0; i < locationsCount; i++)
	{
		sprintf(path, "game/%s/location/%d/ground.loc", gameName, i + 1);
		locations[i] = new Location();
		if (locations[i]->Load(path)) //LocationsInit fails if at least one location failed to load
		{
			for (int j = 0; j <= i; j++)
				delete locations[i];
			delete locations;
			delete path;
			return true;
		}
	}
	SelectLocation(locations[0]);
	delete path;
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
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + i), Index2Pix(cursorY - currentBrush->width/2 + j));
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + i) + cellSize, Index2Pix(cursorY - currentBrush->width/2 + j));
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + i) + cellSize, Index2Pix(cursorY - currentBrush->width/2 + j) + cellSize);
					glVertex2d(Index2Pix(cursorX - currentBrush->width/2 + i), Index2Pix(cursorY - currentBrush->width/2 + j) + cellSize);
				}
			}
		}
	glEnd();

	toolbar->draw();

	glFlush();
	SDL_GL_SwapBuffers();
}

void Universe::SelectLocation(Location* location)
{
	currentLocation = location;
}

void Universe::Run()
{
	Uint8 *keys;
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	int mouseX, mouseY;
	bool continueFlag;

	GraphicsInit();
	GUIInit(GUIInput);
	LocationsInit();
	
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
				{
					for (int i = 0; i < currentBrush->width; i++)
						for (int j = 0; j < currentBrush->width; j++)
							if ((cursorX - currentBrush->width/2 + j) >= 0 && 
								(cursorY - currentBrush->width/2 + i) >= 0 && 
								(cursorX - currentBrush->width/2 + j) < currentLocation->width && 
								(cursorY - currentBrush->width/2 + i) < currentLocation->height
								)
								currentLocation->mask[cursorY - currentBrush->width/2 + i][cursorX - currentBrush->width/2 + j].cellProperty = currentCellProperty;
				}
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
	int i, count;
	char** files;

	//TODO: Remove it when ReadDir will work
	brushes = new CursorBrush*[2];
	brushes[0] = new CursorBrush(1);
	brushes[1] = new CursorBrush(2);
	brushesCount = 2;
	currentBrush = brushes[0];
	return false;

	count = ReadDir("editor\\brush", files, false);
	if (!count)
		return true;
	brushes = new CursorBrush*[count];
	for (i = 0; i < count; i++)
	{
		files[i][strlen(files[i]) - 4] = '\0';
		brushes[i] = new CursorBrush(Str2Int(files[i]));
		delete files[i];
	}
	brushesCount = count;
	currentBrush = brushes[0];
	delete files;
	return false;
}
