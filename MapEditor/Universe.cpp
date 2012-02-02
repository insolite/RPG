#include "StdAfx.h"
#include "Universe.h"

Universe::Universe(void)
{
	cameraX = 0;
	cameraY = 0;
	screenWidth = 800;
	screenHeight = 600;
	cellSize = 64;
	//currentBrush = CellProperty::Free;
	currentBrush = CellProperty::Locked;
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

	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, screenWidth, 0, screenHeight, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);

	return false;
}

void Universe::CameraMove(int x, int y)
{
	if ((cameraX + x) >= 0 && (cameraY + y) >= 0 && 
		(cameraX + (x - 1) * cellSize + screenWidth) < currentLocation->width * cellSize && 
		(cameraY + (y - 1) * cellSize + screenHeight) < currentLocation->height * cellSize)
	{
		cameraX += x;
		cameraY += y;
	}
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
	//glBindTexture(GL_TEXTURE_2D, texture[1].texID);
	glLoadIdentity();
	glTranslated(0, screenHeight, 0);
	//glTranslated(-cameraX * cellSize, cameraY * cellSize, 0); //Camera positioning
	glTranslated(-cameraX, cameraY, 0); //Camera positioning
	glRotatef(180, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
	for (i = 0; i < location->width; i++)
	{
		for (j = 0; j < location->height; j++)
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
			glVertex2d(i * cellSize, j * cellSize);
			glVertex2d(i * cellSize, j * cellSize + cellSize);
			glVertex2d(i * cellSize + cellSize, j * cellSize + cellSize);
			glVertex2d(i * cellSize + cellSize, j * cellSize);
		}
	}
	glEnd();
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		glVertex2d(PixRound(cameraX) + cursorX * cellSize + cellSize, PixRound(cameraY) + cursorY * cellSize + cellSize);
		glVertex2d(PixRound(cameraX) + cursorX * cellSize + cellSize, PixRound(cameraY) + cursorY * cellSize);
		glVertex2d(PixRound(cameraX) + cursorX * cellSize, PixRound(cameraY) + cursorY * cellSize);
		glVertex2d(PixRound(cameraX) + cursorX * cellSize, PixRound(cameraY) + cursorY * cellSize + cellSize);
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

	GraphicsInit();
	LocationsInit();
	
	mouseX = 0;
	mouseY = 0;
	
	while (true)
	{
		SDL_PollEvent(&event);
		keys = SDL_GetKeyState(NULL);
		SDL_PumpEvents();
		//EXIT
		if (keys[SDLK_ESCAPE])
		{
			break;
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
		
		if (event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			//cursorX = Pix2Index(mouseX);
			//cursorY = Pix2Index(mouseY);
			cursorX = Pix2Index(mouseX + cameraX % cellSize);
			cursorY = Pix2Index(mouseY + cameraY % cellSize);

			//printf("%d\n", cursorX);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			currentLocation->mask[cursorX][cursorY].cellProperty = currentBrush;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			
		}

		DDraw(currentLocation);
		//DrawScene();
		glFlush();
		SDL_GL_SwapBuffers();
	}
}
