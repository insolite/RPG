#include "StdAfx.h"
#include "Universe.h"

#define CELL_SIZE 32

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
 
	SDL_SetVideoMode(800, 600, 32, flags);

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);

	return false;
}

void Universe::CameraMove(int x, int y)
{
	if ((cameraX + x) >= 0 && (cameraY - y) >= 0)
	{
		cameraX += x;
		cameraY -= y;
	}
}

void Universe::DrawScene()
{
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
}

void Universe::DDraw(Location* location, int cursorX, int cursorY)
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, texture[1].texID);
	glLoadIdentity();
	//glTranslatef(100.5f, 100.5f, -1.0f);
	if ((PixRound(cursorX - cameraX) >=0 && PixRound(cursorX - cameraX) < 16) || ((PixRound(cursorY + cameraY) >=0) && PixRound(cursorY + cameraY)<16) )
		glTranslated(0 + cameraX, 600 + cameraY, 0);
	else
		glTranslated(0, 600, 0);
	glRotatef(180,1.0f,0.0f,0.0f);
	//glTranslated(0, 0, -10);
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
		if ((cursorX - cameraX) >=0 && (cursorY + cameraY) >= 0)
		{
			glVertex2d(PixRound(cursorX - cameraX) + CELL_SIZE, PixRound(cursorY + cameraY) + CELL_SIZE);
			glVertex2d(PixRound(cursorX - cameraX) + CELL_SIZE, PixRound(cursorY + cameraY));
			glVertex2d(PixRound(cursorX - cameraX), PixRound(cursorY + cameraY));
			glVertex2d(PixRound(cursorX - cameraX), PixRound(cursorY + cameraY) + CELL_SIZE);
		}
	glEnd();
	angle+=0.1;
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
			CameraMove(1, 1);
		}
		//CAMERA UP RIGHT
		else if (keys[SDLK_UP] && keys[SDLK_RIGHT])
		{
			CameraMove(-1, 1);
		}
		//CAMERA DOWN LEFT
		else if (keys[SDLK_DOWN] && keys[SDLK_LEFT])
		{
			CameraMove(1, -1);
		}
		//CAMERA DOWN RIGHT
		else if (keys[SDLK_DOWN] && keys[SDLK_RIGHT])
		{
			CameraMove(-1, -1);
		}
		//CAMERA UP
		else if (keys[SDLK_UP])
		{
			CameraMove(0, 1);
		}
		//CAMERA DOWN
		else if (keys[SDLK_DOWN])
		{
			CameraMove(0, -1);
		}
		//CAMERA LEFT
		else if (keys[SDLK_LEFT])
		{
			CameraMove(1, 0);
		}
		//CAMERA RIGHT
		else if (keys[SDLK_RIGHT])
		{
			CameraMove(-1, 0);
		}
		
		if (event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		DDraw(currentLocation, mouseX, mouseY);
		//DrawScene();
		glFlush();
		SDL_GL_SwapBuffers();
	}
}
