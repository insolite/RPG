#include "StdAfx.h"
#include "Universe.h"
#include "SliderActionListener.h"

Universe::Universe(void)
{
	screenWidth = 800;
	screenHeight = 600;
	fullscreen = false;
	/*
	screenWidth = 1366;
	screenHeight = 768;
	fullscreen = true;
	*/
	cellSize = 64;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
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
	Uint32 flags = SDL_OPENGL;
	
	if (fullscreen)
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

bool Universe::MenuGUIInit(gcn::SDLInput* &GUIInput)
{
	char fontCharacters[256];
	FILE* f;

	//Input init
	GUIInput = new gcn::SDLInput();

	//Font init
	f = fopen("editor/_font/char.txt", "rt");
	if (!f)
		return true;
	fgets(fontCharacters, 256, f);
	fclose(f);
	gcn::Image::setImageLoader(new gcn::OpenGLSDLImageLoader());
	gcn::ImageFont* mFontWhite = new gcn::ImageFont("editor/_font/face.png", fontCharacters);
	gcn::Widget::setGlobalFont(mFontWhite);
	
	//Main container init
	menuMainContainer = new gcn::Container();
	menuMainContainer->setDimension(gcn::Rectangle(0, 0, screenWidth, screenHeight));
	//menuMainContainer->setOpaque(false);

	//GUI init
	menuGUI= new gcn::Gui();
	graphics = new gcn::OpenGLGraphics(screenWidth, screenHeight);
	menuGUI->setGraphics(graphics);
	menuGUI->setInput(GUIInput);
	menuGUI->setTop(menuMainContainer);

	//GUI building
	
	//Some graphical elements
	//...
	
	//Games list
	//Game select ListBox
	char** games;
	int gamesCount;
	gamesCount = ReadDir("game", games, true);
	gamesListModel = new StringListModel();
	for (int i = 0; i < gamesCount; i++)
		gamesListModel->add(games[i]);
	delete[] games;
	gamesListBox = new gcn::ListBox(gamesListModel);
	gamesListBox->setSelected(0);
	//TODO:
	//Auto resize ListBox. adjustSize doesn't work for width. Sadly...
	gamesListBox->setSize(512, 0);
	gamesListBox->adjustSize();
	gamesListBoxScrollArea = new gcn::ScrollArea();
	gamesListBoxScrollArea->setHorizontalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	gamesListBoxScrollArea->setVerticalScrollPolicy(gcn::ScrollArea::SHOW_AUTO);
	gamesListBoxScrollArea->setContent(gamesListBox);
	gamesListBoxScrollArea->setSize(256, 320);
	menuMainContainer->add(gamesListBoxScrollArea, 256, 64);

	//New game window
	newGameWindow = new NewGameWindow("New game");
	
	//Buttons init
	newGameButton = new ToggleWindowVisibilityButton("New", newGameWindow);
	loadGameButton = new LoadGameButton("Load");
	deleteGameButton = new DeleteGameButton("Delete", gamesListBox);
	quitButton = new gcn::Button("Quit");
	newGameButton->setWidth(128);
	loadGameButton->setWidth(128);
	deleteGameButton->setWidth(128);
	quitButton->setWidth(128);
	menuMainContainer->add(newGameButton, 520, 64);
	menuMainContainer->add(loadGameButton, 520, 96);
	menuMainContainer->add(deleteGameButton, 520, 128);
	menuMainContainer->add(quitButton, 520, 360);

	menuMainContainer->add(newGameWindow, screenWidth / 2 - newGameWindow->getWidth() / 2, screenHeight / 2 - newGameWindow->getHeight() / 2);
}

bool Universe::EditorGUIInit(gcn::SDLInput* &GUIInput)
{
	//Input init
	GUIInput = new gcn::SDLInput();

	//Edit area container init
	editAreaContainer = new gcn::Container();
	editAreaContainer->setDimension(gcn::Rectangle(0, 0, screenWidth - toolbarWidth, screenHeight));
	editAreaContainer->setOpaque(false);
	editAreaContainer->setFocusable(true);

	//Toolbar container init
	toolbarContainer = new FocusingWindow("Tools");
	toolbarContainer->setDimension(gcn::Rectangle(0, 0, toolbarWidth, screenHeight));
	toolbarContainer->setFocusable(true);
	toolbarContainer->setMovable(false);
	
	//Main container init
	editorMainContainer = new gcn::Container();
	editorMainContainer->setDimension(gcn::Rectangle(0, 0, screenWidth, screenHeight));
	editorMainContainer->setOpaque(false);
	editorMainContainer->add(editAreaContainer, 0, 0);
	editorMainContainer->add(toolbarContainer, screenWidth - toolbarWidth, 0);
	
	//GUI init
	editorGUI = new gcn::Gui();
	editorGUI->setGraphics(graphics);
	editorGUI->setInput(GUIInput);
	editorGUI->setTop(editorMainContainer);

	//GUI building

	//Floor control DropDown
	FloorDropDown* floorsDropDown = new FloorDropDown();
	floorsDropDown->add("outside");
	floorsDropDown->add("first fl.");
	floorsDropDown->setSelected(0);
	toolbarContainer->add(floorsDropDown, toolbarLeftMargin, 16);

	//Location control DropDown
	LocationDropDown* locationsDropDown = new LocationDropDown();
	for (int i = 0; i < game->data->locationsCount; i++)
		locationsDropDown->add(game->data->locations[i]->name);
	locationsDropDown->setSelected(0);
	toolbarContainer->add(locationsDropDown, toolbarLeftMargin, 40);
	
	//MapCell select window
	mapCellSelectWindow = new MapObjectSelectWindow("MapCell selection", (MapObject**)game->resources->mapCells, game->resources->mapCellsCount, 0); //TODO: explicit convertion? Really? o_0
	editorMainContainer->add(mapCellSelectWindow);
	
	//NPC select window
	npcSelectWindow = new MapObjectSelectWindow("NPC selection", (MapObject**)game->resources->npcs, game->resources->npcsCount, 1); //TODO: explicit convertion? Really? o_0
	editorMainContainer->add(npcSelectWindow);
	
	//Static select window
	staticSelectWindow = new MapObjectSelectWindow("Static selection", (MapObject**)game->resources->statics, game->resources->staticsCount, 2); //TODO: explicit convertion? Really? o_0
	editorMainContainer->add(staticSelectWindow);
	
	//Item select window
	itemSelectWindow = new MapObjectSelectWindow("Item selection", (MapObject**)game->resources->items, game->resources->itemsCount, 3); //TODO: explicit convertion? Really? o_0
	editorMainContainer->add(itemSelectWindow);
	
	int brushMaskMinSize = 1;
	int brushMaskMaxSize = 10;

	//Brush mask size slider
	brushMaskSlider = new gcn::Slider(brushMaskMinSize - 0.5f, brushMaskMaxSize - 0.5f);
	brushMaskSlider->setOrientation(gcn::Slider::HORIZONTAL);
	brushMaskSlider->setSize(128, 12);
	//brushMaskSlider->setStepLength(1); //Only for keyboard //Isn't needed due to line below
	brushMaskSlider->setFocusable(false);
	gcn::ActionListener* actionListener = new SliderActionListener();
	brushMaskSlider->addActionListener(actionListener);

	//Brush mask size label
	brushMaskSizeLabel = new gcn::Label("1x");
	brushMaskSizeLabel->setSize(32, 16);

	//MapCells tab container (#1)
	mapCellSelectTabContainer = new MapObjectSelectTabContainer(mapCellSelectWindow);
	mapCellSelectTabContainer->add(brushMaskSlider, 36, 204);
	mapCellSelectTabContainer->add(brushMaskSizeLabel, 4, 200);

	//Statics tab container (#2)
	npcSelectTabContainer = new MapObjectSelectTabContainer(npcSelectWindow);

	//Statics tab container (#3)
	staticSelectTabContainer = new MapObjectSelectTabContainer(staticSelectWindow);
	
	//Statics tab container (#4)
	itemSelectTabContainer = new MapObjectSelectTabContainer(itemSelectWindow);

	//MapObjects selection TabbedArea
	gcn::TabbedArea* brushesTabbedArea = new gcn::TabbedArea();
	brushesTabbedArea->setSize(176, 256);
	brushesTabbedArea->addTab("Cell", mapCellSelectTabContainer);
	brushesTabbedArea->addTab("NPC", npcSelectTabContainer);
	brushesTabbedArea->addTab("Stat.", staticSelectTabContainer);
	brushesTabbedArea->addTab("Item", itemSelectTabContainer);
	toolbarContainer->add(brushesTabbedArea, toolbarLeftMargin, 96);
	
	return false;
}

void Universe::EditorGUIDestroy()
{
	delete editorGUI;
	delete toolbarContainer;
	delete editorMainContainer;
	delete editAreaContainer;
	delete mapCellSelectWindow;
	delete npcSelectWindow;
	delete staticSelectWindow;
	delete itemSelectWindow;

	delete brushMaskSlider;
	delete brushMaskSizeLabel;

	delete mapCellSelectTabContainer;
	delete npcSelectTabContainer;
	delete staticSelectTabContainer;
	delete itemSelectTabContainer;
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

void Universe::DrawMenu()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	menuGUI->draw();

	//glFlush();
	SDL_GL_SwapBuffers();
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
				case Free:
					glColor4d(0, 1, 0, 1);
					break;
				case Locked:
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
				if (currentBrushMask->data[i][j])
				{
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j), Index2Pix(cursorY - currentBrushMask->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrushMask->width/2 + i));
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j) + cellSize, Index2Pix(cursorY - currentBrushMask->width/2 + i) + cellSize);
					glVertex2d(Index2Pix(cursorX - currentBrushMask->width/2 + j), Index2Pix(cursorY - currentBrushMask->width/2 + i) + cellSize);
				}
			}
		}
	glEnd();

	editorGUI->draw();

	//glFlush();
	SDL_GL_SwapBuffers();
}

void Universe::SetLocation(Location* location)
{
	CameraReset();
	CursorReset();
	currentLocation = location;
}

char* Universe::Menu()
{
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	bool continueFlag;
	
	GraphicsInit();
	MenuGUIInit(GUIInput);

	continueFlag = true;
	loadGameButton->continueFlag = &continueFlag;
	
	int lastUpdate = SDL_GetTicks();

	while (continueFlag)
	{
		SDL_PumpEvents();
		
		while (SDL_PollEvent(&event))
		{
			GUIInput->pushInput(event); //((gcn::SDLInput*)(toolbar->getInput()))->pushInput(event); //This code doing the same without defined pointer to GUIInput, but looks too bad...
			menuGUI->logic();
		}

		switch (event.type)
		{
			case SDL_QUIT:
				return NULL;
		}

		if ((SDL_GetTicks() - lastUpdate) > 40) //14 for 60fps, 22 for 41fps, 40 for 24fps
		{
			DrawMenu();
			lastUpdate = SDL_GetTicks();
		}
		Sleep(1);
	}

	return (char*)gamesListModel->getElementAt(gamesListBox->getSelected()).c_str();
}

void Universe::Run(char* gameName)
{
	Uint8 *keys;
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	int mouseX, mouseY;
	bool continueFlag;

	game = new Game(gameName);
	game->Init();
	BrushesInit();

	CameraReset();
	CursorReset();

	EditorGUIInit(GUIInput);

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
			editorGUI->logic();
		}

		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1))
		{
			if (editAreaContainer->isFocused())
				PaintMapCell();
		}

		//TODO: Put this inside the switch below
		//EXIT
		if (keys[SDLK_UP] && keys[SDLK_LEFT])
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
				if (event.key.keysym.sym == SDLK_ESCAPE)
					continueFlag = false;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
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
		
		if ((SDL_GetTicks() - lastUpdate) > 40) //14 for 60fps, 22 for 41fps, 40 for 24fps
		{
			DrawScene();
			lastUpdate = SDL_GetTicks();
		}
		Sleep(1);
	}

	EditorGUIDestroy();
	delete game;
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
				brushMasks[k]->data[i][j] = fgetc(f) ? true : false; //the same as fgetc(f), but VC warnings...
	}
	fclose(f);
	brushesCount = count;
	currentBrushMask = brushMasks[0];

	brush[0] = game->resources->mapCells[1];
	/*
	brush[1] = game->resources->npcs[0];
	brush[2] = game->resources->statics[0];
	brush[3] = game->resources->items[0];
	*/
	brushIndex = 0;

	return false;
}

void Universe::PaintMapCell()
{
	int i, j;
	MapCell* pBrush;
	
	pBrush = (MapCell*)brush[brushIndex];
	
	for (i = 0; i < currentBrushMask->width; i++)
	{
		for (j = 0; j < currentBrushMask->width; j++)
		{
			if ((cursorX - currentBrushMask->width/2 + j) >= 0 && 
				(cursorY - currentBrushMask->width/2 + i) >= 0 && 
				(cursorX - currentBrushMask->width/2 + j) < currentLocation->width && 
				(cursorY - currentBrushMask->width/2 + i) < currentLocation->height && 
				currentBrushMask->data[i][j])
				currentLocation->mask[cursorY - currentBrushMask->width/2 + i][cursorX - currentBrushMask->width/2 + j] = pBrush;
		}
	}
	/*
	//Static* pBrush = (Static*)brush[brushIndex];
	pBrush = (Static*)brush[brushIndex];
	for (i = 0; i < pBrush->mask->width; i++)
	{
		for (j = 0; j < pBrush->mask->width; j++)
		{
			if ((cursorX - pBrush->mask->width/2 + j) >= 0 && 
				(cursorY - pBrush->mask->width/2 + i) >= 0 && 
				(cursorX - pBrush->mask->width/2 + j) < currentLocation->width && 
				(cursorY - pBrush->mask->width/2 + i) < currentLocation->height && 
				(*pBrush->mask)[i][j])
				currentLocation->mask[cursorY - pBrush->mask->width/2 + i][cursorX - pBrush->mask->width/2 + j]->cellProperty = CellProperty::Locked; // ((Static*)brush[brushIndex])->mask->mask[i][j];
		}
	}
	*/
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
