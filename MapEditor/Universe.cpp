#include "StdAfx.h"
#include "Universe.h"
#include "MenuButton.h"

Universe::Universe(void)
{
	cameraX = 0;
	cameraY = 0;
	screenWidth = 800;
	screenHeight = 600;
	cellSize = 64;
	//currentBrush = CellProperty::Free;
	currentBrush = CellProperty::Locked;
	toolbarWidth = 128;
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

	return true;
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
	/*
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture[1].texID);
	glLoadIdentity();
	glTranslatef(100.5f, 100.5f, -1.0f);
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2d(-10, -10);
	glVertex2d(-10, 10);
	glVertex2d(10, 10);
	glVertex2d(10, -10);
	glEnd();
	*/
}

void Universe::DDraw(Location* location)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(-cameraX, -cameraY, 0); //Camera positioning
	
	glBegin(GL_QUADS);
	for (i = 0; i < location->height; i++)
	{
		for (j = 0; j < location->width; j++)
		{
			switch (location->mask[i][j].cellProperty)
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
		glVertex2d(Index2Pix(cursorX), Index2Pix(cursorY));
		glVertex2d(Index2Pix(cursorX) + cellSize, Index2Pix(cursorY));
		glVertex2d(Index2Pix(cursorX) + cellSize, Index2Pix(cursorY) + cellSize);
		glVertex2d(Index2Pix(cursorX), Index2Pix(cursorY) + cellSize);
	glEnd();
}

void Universe::SelectLocation(Location* location)
{
	currentLocation = location;
}

void Universe::LocationsInit()
{
	locations = new (Location*[1]);
	locations[0] = new Location;
	locations[0]->Load("test.loc");
	SelectLocation(locations[0]);
}

void Universe::Run()
{
	Uint8 *keys;
	SDL_Event event;
	int mouseX, mouseY;
	bool continueFlag;

	GraphicsInit();
	LocationsInit();
	
	//locations[0]->Print();

	mouseX = 0;
	mouseY = 0;

	continueFlag = true;

	//Input init
	gcn::SDLInput* mSDLInput = new gcn::SDLInput();

	//Container init
	gcn::Container* toolbarContainer = new gcn::Container();
	toolbarContainer->setBaseColor(gcn::Color(0x000000));
	toolbarContainer->setDimension(gcn::Rectangle(screenWidth - toolbarWidth, 0, toolbarWidth, screenHeight));

	//GUI init
	gcn::Gui* toolbar = new gcn::Gui();
	toolbar->setGraphics(new gcn::OpenGLGraphics(screenWidth, screenHeight));
	toolbar->setInput(mSDLInput);
	toolbar->setTop(toolbarContainer);

	//Font init
	gcn::Image::setImageLoader(new gcn::OpenGLSDLImageLoader());
	gcn::ImageFont* mFontWhite = new gcn::ImageFont("rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
	//gcn::Widget::setGlobalFont(mFontWhite);
	//gcn::Button::setGlobalFont(mFontWhite);

	//GUI building
	MenuButton* testButton = new MenuButton("Test");
	testButton->setFont(mFontWhite);
	toolbarContainer->add(testButton, 64, 64);
	
	while (continueFlag)
	{
		//TODO: while (SDL_PollEvent(&event)) {...}
		SDL_PollEvent(&event);
		keys = SDL_GetKeyState(NULL);
		SDL_PumpEvents();
		
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
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (mouseX < (screenWidth - toolbarWidth)) //Prevents drawing cells with brush while mouse cursor is on the toolbar
					currentLocation->mask[cursorY][cursorX].cellProperty = currentBrush;
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				continueFlag = false;
				break;
		}

		if (mouseX < (screenWidth - toolbarWidth)) //Prevents cursor moving while mouse cursor is on the toolbar
		{
			cursorX = Pix2Index(mouseX + cameraX);
			cursorY = Pix2Index(mouseY + cameraY);
		}
		//printf("%d : %d\n", cursorX, cursorY);

		DDraw(currentLocation);
		mSDLInput->pushInput(event);
		toolbar->logic();
		toolbar->draw();
		//DrawScene();
		glFlush();
		SDL_GL_SwapBuffers();
	}
}
