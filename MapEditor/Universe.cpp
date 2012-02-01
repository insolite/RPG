#include "StdAfx.h"
#include "Universe.h"

#define CELL_SIZE 64

GLfloat angle;
int Pix2Index(int pos)
{
	return pos / CELL_SIZE;
}

int Index2Pix(int pos)
{
	return pos * CELL_SIZE;
}

int PixRound(int pos)
{
	return Index2Pix(Pix2Index(pos));
}


Universe::Universe(void)
{
	cameraX = 0;
	cameraY = 0;
	screenWidth = 800;
	screenHeight = 600;
}

Universe::~Universe(void)
{
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
		((cameraX + x - 1) * CELL_SIZE + screenWidth) < currentLocation->width * CELL_SIZE && 
		((cameraY + y - 1) * CELL_SIZE + screenHeight) < currentLocation->height * CELL_SIZE)
	{
		cameraX += x;
		cameraY += y;
		cursorX += x;
		cursorY += y;
	}
	Sleep(64);
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
	glTranslated(-cameraX * CELL_SIZE, cameraY * CELL_SIZE, 0); //Camera positioning
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
			glVertex2d(i * CELL_SIZE, j * CELL_SIZE);
			glVertex2d(i * CELL_SIZE, j * CELL_SIZE + CELL_SIZE);
			glVertex2d(i * CELL_SIZE + CELL_SIZE, j * CELL_SIZE + CELL_SIZE);
			glVertex2d(i * CELL_SIZE + CELL_SIZE, j * CELL_SIZE);
		}
	}
	glEnd();
	glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
		glVertex2d(cursorX * CELL_SIZE + CELL_SIZE, cursorY * CELL_SIZE + CELL_SIZE);
		glVertex2d(cursorX * CELL_SIZE + CELL_SIZE, cursorY * CELL_SIZE);
		glVertex2d(cursorX * CELL_SIZE, cursorY * CELL_SIZE);
		glVertex2d(cursorX * CELL_SIZE, cursorY * CELL_SIZE + CELL_SIZE);
	glEnd();
	angle += 0.1;
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
			cursorX = cameraX + Pix2Index(mouseX);
			cursorY = cameraY + Pix2Index(mouseY);
		}

		DDraw(currentLocation);
		//DrawScene();
		glFlush();
		SDL_GL_SwapBuffers();
	}
}
