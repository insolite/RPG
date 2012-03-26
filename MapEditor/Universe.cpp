#include "StdAfx.h"
#include "Universe.h"
#include "SliderActionListener.h"

Universe::Universe(void)
{
	char fontCharacters[256];
	FILE* f;

	screenWidth = 800;
	screenHeight = 600;
	fullscreen = false;
	/*
	screenWidth = 1366;
	screenHeight = 768;
	fullscreen = true;
	*/
	cellSize = 10;
	cameraMoveZoneWidth = 24;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
	brushMaskMinSize = 1;
	brushMaskMaxSize = 10;
	instance = this;

	render = new Render(screenWidth, screenHeight);
	//GraphicsInit();
	
	/*
	graphics = new gcn::OpenGLGraphics(screenWidth, screenHeight);
	gcn::Image::setImageLoader(new gcn::OpenGLSDLImageLoader());

	//Font init
	f = fopen("editor/_font/char.txt", "rt");
	if (!f)
		return;
	fgets(fontCharacters, 256, f);
	fclose(f);
	
	gcn::Widget::setGlobalFont(new gcn::ImageFont("editor/_font/face.png", fontCharacters));*/
}

Universe::~Universe(void)
{
	delete graphics;
	//TODO: delete image loader, font
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
	/*
	Uint32 flags = SDL_OPENGL;
	
	if (fullscreen)
		flags |= SDL_FULLSCREEN;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return true;
	}
	SDL_WM_SetCaption("RPG", NULL);

	SDL_EnableUNICODE(1); //For gcn input

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
	*/
	
	return false;
}

void Universe::MenuGUIInit(gcn::SDLInput* &GUIInput)
{
	//Input init
	GUIInput = new gcn::SDLInput();

	//Main container init
	menuMainContainer = new gcn::Container();
	menuMainContainer->setDimension(gcn::Rectangle(0, 0, screenWidth, screenHeight));
	//menuMainContainer->setOpaque(false);
	
	//GUI init
	menuGUI = new gcn::Gui();
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
	{
		gamesListModel->add(games[i]);
		delete games[i];
	}
	delete games;
	
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
	quitButton = new QuitButton("Quit");
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

enum EditorGUIElements
{
	QuitButton,
	ToolBarWindow,
	FloorsComboBox,
	LocationsComboBox,
	MapObjectsTabControl,
	BrushMaskSizeScroll,
	BrushMaskSizeStaticText,

	//Order is critical
	MapCellSelectWindow,
	NPCSelectWindow,
	ItemSelectWindow,
	StaticSelectWindow,
	CharacterSelectWindow,
	MapCellSelectWindowTab,
	NPCSelectWindowTab,
	ItemSelectWindowTab,
	StaticSelectWindowTab,
	CharacterSelectWindowTab,
	MapCellSelectWindowToggleButton,
	NPCSelectWindowToggleButton,
	ItemSelectWindowToggleButton,
	StaticSelectWindowToggleButton,
	CharacterSelectWindowToggleButton,
};

wchar_t* strToWchart(char* cStr) 
{
	wchar_t* wCharOutput = new wchar_t[1023];
	size_t* sizeOut = new size_t;
	size_t sizeInWords = 256;

	mbstowcs_s(sizeOut, wCharOutput, sizeInWords, cStr, strlen(cStr) + 1);

	return wCharOutput;
}

void Universe::EditorGUIInit()
{
	IGUIWindow* wnd = render->guienv->addWindow(rect< s32 >(screenWidth - toolbarWidth, 0, screenWidth, screenHeight), false, L"Toolset", 0, ToolBarWindow);
	
	IGUIButton* btn = render->guienv->addButton(rect< s32 >(10, 128, 110, 128 + 32), wnd, QuitButton, L"Quit", L"Exits Program");
	
	//Floors ComboBox
	IGUIComboBox* floorsComboBox = render->guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 32, toolbarLeftMargin + 176, 48), wnd, FloorsComboBox);
	floorsComboBox->addItem(L"outside");
	floorsComboBox->addItem(L"first fl.");
	
	//Locations ComboBox
	IGUIComboBox* locationsComboBox = render->guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 64, toolbarLeftMargin + 176, 80), wnd, LocationsComboBox);
	for (int i = 0; i < game->data->locationsCount; i++)
	{
		wchar_t* wstr = strToWchart(game->data->locations[i]->name);
		locationsComboBox->addItem(wstr);
		delete wstr;
	}

	//MapObject select windows, tabs, buttons, etc.
	IGUITabControl* tabc = render->guienv->addTabControl(rect< s32 >(toolbarLeftMargin, 256, toolbarLeftMargin + 176, 256 + 176), wnd, true, true, MapObjectsTabControl);
	IGUIWindow* wnd1;
	IGUITab* tab;
	for (int i = 0; i < 5; i++)
	{
		wnd1 = render->guienv->addWindow(rect< s32 >(64, 64, 536, 536), false, L"MapObject select", 0, i + MapCellSelectWindow);
		wnd1->setVisible(false);
		tab = tabc->addTab(L"MO", i + MapCellSelectWindowTab);
		render->guienv->addButton(rect< s32 >(16, 16, 32, 32), tab, i + MapCellSelectWindowToggleButton, L"Select", L"Select MapObject from list");
	}
	
	//Brush mask scroll bar
	IGUIScrollBar* sb = render->guienv->addScrollBar(true, rect< s32 >(8, 64, 168, 80), tabc->getTab(0), BrushMaskSizeScroll);
	sb->setMax(10);
	sb->setMin(1);
	sb->setPos(3);
	//render->guienv->addSpinBox(L"asd", rect< s32 >(toolbarLeftMargin, 432, toolbarLeftMargin + 176, 464), true, wnd);

	IGUIStaticText* lbl = render->guienv->addStaticText(L"3x", rect< s32 >(8, 88, 168, 104), false, false, tabc->getTab(0), BrushMaskSizeStaticText, true);

	wnd->setDraggable(false); //TEST
	wnd->getCloseButton()->setEnabled(false); //TEST

	//render->guienv->getSkin()->setFont(render->guienv->getBuiltInFont(), EGDF_TOOLTIP);
}

void Universe::MenuGUIDestroy(gcn::SDLInput* GUIInput)
{
	delete GUIInput;
	delete menuGUI;
	delete menuMainContainer;
	delete newGameButton;
	delete loadGameButton;
	delete deleteGameButton;
	delete quitButton;
	delete gamesListModel;
	delete gamesListBox;
	delete gamesListBoxScrollArea;
	delete newGameWindow;
}

void Universe::EditorGUIDestroy(gcn::SDLInput* GUIInput)
{
	delete GUIInput;
	delete editorGUI;
	delete toolbarContainer;
	delete editorMainContainer;
	delete editAreaContainer;
	delete mapCellSelectWindow;
	delete npcSelectWindow;
	delete staticSelectWindow;
	delete itemSelectWindow;

	delete floorsDropDown;
	delete locationsDropDown;
	delete actionListener;
	delete brushesTabbedArea;

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
	int i, j, drawWidth, drawHeight;

	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(-cameraX, -cameraY, 0); //Camera positioning
	
	drawWidth = Pix2Index(cameraX + screenWidth) + 1;
	drawHeight = Pix2Index(cameraY + screenHeight) + 1;
	if (drawWidth > currentLocation->width)
		drawWidth = currentLocation->width;
	if (drawHeight > currentLocation->height)
		drawHeight = currentLocation->height;*/
	//for (i = 0; i < currentLocation->height; i++)
	for (i = 0; i < currentLocation->height; i++)
	{
		//for (j = 0; j < currentLocation->width; j++)
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j]->cellProperty)
			{
				case Free:
					render->drawKub(j*cellSize,-20,i*cellSize);
					break;
				/*case Locked:
					glColor4d(1, 0, 0, 0.5);
					break;
				default:
					glColor4d(1, 1, 1, 1);*/
			}
			/*glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize);
			glTexCoord2f(1.0f, 0.0f); glVertex2d(j * cellSize, i * cellSize + cellSize);
			glTexCoord2f(1.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize + cellSize);
			glTexCoord2f(0.0f, 1.0f); glVertex2d(j * cellSize + cellSize, i * cellSize);
			glEnd();*/
		}
	}
}

void Universe::SetLocation(Location* location)
{
	//CameraReset();
	//CursorReset();
	currentLocation = location;
}

bool Universe::Menu(char* &gameName)
{
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	char continueFlag;
	
	MenuGUIInit(GUIInput);
	
	continueFlag = 1;
	loadGameButton->continueFlag = &continueFlag;
	quitButton->continueFlag = &continueFlag;
	
	int lastUpdate = SDL_GetTicks();
	
	while (continueFlag)
	{
		SDL_PumpEvents();
		
		while (SDL_PollEvent(&event))
		{
			GUIInput->pushInput(event);
			menuGUI->logic();
		}

		switch (event.type)
		{
			case SDL_QUIT:
				return true;
		}

		if ((SDL_GetTicks() - lastUpdate) > 40) //14 for 60fps, 22 for 41fps, 40 for 24fps
		{
			DrawMenu();
			lastUpdate = SDL_GetTicks();
		}
		Sleep(1);

		if (continueFlag == 2)
			return true;
	}
	
	gameName = new char[gamesListModel->getElementAt(gamesListBox->getSelected()).length() + 1];
	strcpy(gameName, gamesListModel->getElementAt(gamesListBox->getSelected()).c_str());
	
	MenuGUIDestroy(GUIInput);

	return false;
}

void Universe::Run(char* gameName)
{
	/*
	Uint8 *keys;
	SDL_Event event;
	gcn::SDLInput* GUIInput;
	int mouseX, mouseY;
	bool continueFlag;

	game = new Game(gameName, Editor);
	SetLocation(game->data->locations[0]);
	
	BrushesInit();
	
	CameraReset();
	CursorReset();

	EditorGUIInit(GUIInput);
	
	CreateBrushMask(brushMaskSlider->getValue());

	//TESTTESTTESTTESTTESTTEST
	LoadTexture();

	mouseX = 0;
	mouseY = 0;

	continueFlag = true;
	
	//keys = SDL_GetKeyState(NULL);
	//SDL_GetMouseState(&mouseX, &mouseY);
	int lastUpdate = SDL_GetTicks();
	/*
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

		//CAMERA UP LEFT
		if (keys[SDLK_UP] && keys[SDLK_LEFT] || mouseY < cameraMoveZoneWidth * 3 && mouseX < cameraMoveZoneWidth * 3)
		{
			CameraMove(-1, -1);
		}
		//CAMERA UP RIGHT
		else if (keys[SDLK_UP] && keys[SDLK_RIGHT] || mouseY < cameraMoveZoneWidth * 3 && mouseX > (screenWidth - toolbarWidth - cameraMoveZoneWidth * 3) && mouseX < (screenWidth - toolbarWidth))
		{
			CameraMove(1, -1);
		}
		//CAMERA DOWN LEFT
		else if (keys[SDLK_DOWN] && keys[SDLK_LEFT] || mouseY > (screenHeight - cameraMoveZoneWidth * 3) && mouseX < cameraMoveZoneWidth * 3)
		{
			CameraMove(-1, 1);
		}
		//CAMERA DOWN RIGHT
		else if (keys[SDLK_DOWN] && keys[SDLK_RIGHT] || mouseY > (screenHeight - cameraMoveZoneWidth * 3) && mouseX > (screenWidth - toolbarWidth - cameraMoveZoneWidth * 3) && mouseX < (screenWidth - toolbarWidth))
		{
			CameraMove(1, 1);
		}
		//CAMERA UP
		else if (keys[SDLK_UP] || mouseY < cameraMoveZoneWidth * 3 && mouseX < (screenWidth - toolbarWidth))
		{
			CameraMove(0, -1);
		}
		//CAMERA DOWN
		else if (keys[SDLK_DOWN] || mouseY > (screenHeight - cameraMoveZoneWidth * 3) && mouseX < (screenWidth - toolbarWidth))
		{
			CameraMove(0, 1);
		}
		//CAMERA LEFT
		else if (keys[SDLK_LEFT] || mouseX < cameraMoveZoneWidth * 3)
		{
			CameraMove(-1, 0);
		}
		//CAMERA RIGHT
		else if (keys[SDLK_RIGHT] || mouseX > (screenWidth - toolbarWidth - cameraMoveZoneWidth * 3) && mouseX < (screenWidth - toolbarWidth))
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
	
	//EditorGUIDestroy(GUIInput);

	for (int i = 0; i < brushesCount; i++)
		delete brushMasks[i];
	delete brushMasks;

	//TEST
	DeleteTexture();
	
	delete game;*/
	
	bool continueFlag;
	
	game = new Game(gameName, Editor);
	SetLocation(game->data->locations[0]);

	BrushesInit();
	
	EditorGUIInit();
	
	CreateBrushMask(1); //TODO: slider get value
	
	continueFlag = true;
	
	int lastUpdate = SDL_GetTicks();

	//DrawScene();
	//render->smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	
	render->smgr->addCameraSceneNodeFPS();
	render->device->getCursorControl()->setVisible(false);
	/* //Uncomment it (and comment two lines above) to enable gui control
	//render->smgr->addCameraSceneNodeFPS();
	render->device->getCursorControl()->setVisible(true);
	*/

	DrawScene();
	render->drawKub(0,0,0);
	while (render->device->run() && continueFlag)
	{
		render->driver->beginScene(true, true, SColor(255,100,101,140));
			render->smgr->drawAll();
			render->guienv->drawAll();
		render->driver->endScene();
	}

	//EditorGUIDestroy();

	for (int i = 0; i < brushesCount; i++)
		delete brushMasks[i];
	delete brushMasks;

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

void Universe::CreateBrushMask(int r)
{
	brushRadius = r;

	int y,i,j;
     
	brushMask = new bool*[brushRadius * 2 + 1];
     
	for (i=0; i < 2 * brushRadius + 1; i++)
	{
		brushMask[i] = new bool[2 * brushRadius + 1];
	}
     
	for (i = 0; i < 2 * brushRadius + 1; i++)
		for (j = 0; j < 2 * brushRadius + 1; j++)
			brushMask[i][j] = false;
     
	for (i = 0; i <= brushRadius; i++)
	{
		y = sqrt((double)(brushRadius * brushRadius - i * i));
         
		for (j = brushRadius - y; j <= brushRadius + y; j++)
		{
			brushMask[j][i + brushRadius] = true;
			brushMask[j][(int)abs(i - brushRadius)] = true;   
		}
	}
}

void Universe::PrintBrushMask()
{
	int i,j;

	for (i = 0; i < 2 * brushRadius + 1; i++)
	{
		for (j = 0; j < 2 * brushRadius + 1; j++)
			printf("%3d", brushMask[i][j]);
	
		printf("\n");
	}

	printf("|-------------------------------------------|\n");
}


void Universe::DeleteBrushMask()
{
	for (int i = 0; i < brushRadius * 2 + 1; i++)
		delete brushMask[i];

	delete brushMask;
}

void Universe::PaintMapCell()
{
	int i, j;
	MapCell* pBrush;
	
	pBrush = (MapCell*)brush[brushIndex];
	
	for (i = 0; i < brushRadius * 2 + 1; i++)
	{
		for (j = 0; j < brushRadius * 2 + 1; j++)
		{
			if ((brushMask[i][j]) &&
				(cursorX - brushRadius + j) >= 0 && 
				(cursorY - brushRadius + i) >= 0 && 
				(cursorX - brushRadius + j) < currentLocation->width && 
				(cursorY - brushRadius + i) < currentLocation->height)
				currentLocation->mask[cursorY - brushRadius + i][cursorX - brushRadius + j] = pBrush;
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
	texture = new GLuint[1];

	// Picture loading
	AUX_RGBImageRec *texture1;
	//texture1 = auxDIBImageLoad("grass.bmp");

	// Texture creating
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	delete texture1->data;
	delete texture1;
	
	return true;
}

void Universe::DeleteTexture()
{
	glDeleteTextures(1, texture);
	delete texture;
}
