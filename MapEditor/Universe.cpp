#include "StdAfx.h"
#include "ForcedDeclaration.h"
#include "MenuEventReceiver.h"
#include "EditorEventReceiver.h"
#include "Render.h"
#include "Universe.h"

Universe* Universe::instance;

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
	cameraMoveZoneWidth = 24;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
	brushMaskMinSize = 1;
	brushMaskMaxSize = 10;
	instance = this;

	render = new Render(screenWidth, screenHeight);

	menuEventReceiver = new MenuEventReceiver();
	editorEventReceiver = new EditorEventReceiver();
}

Universe::~Universe(void)
{
}

void Universe::MenuGUIInit()
{
	menuGuienv = render->device->getGUIEnvironment();
	render->device->setEventReceiver((IEventReceiver*)menuEventReceiver);

	char** games;
	int gamesCount;
	gamesCount = ReadDir("game", games, true);
	lb = menuGuienv->addListBox(rect< s32 >(256, 160, 480, 512), NULL, GamesListBox, true);
	for (int i = 0; i < gamesCount; i++)
	{
		wchar_t* wstr = strToWchart(games[i]);
		lb->addItem(wstr);
		delete wstr;
		delete games[i];
	}
	delete games;
	if (lb->getItemCount() > 0)
		lb->setSelected(0);
	
	//IGUIButton* lb = menuGuienv->addListBox(rect< s32 >(128, 128, 256, 512), NULL, GamesListBox, true);
	menuGuienv->addButton(rect< s32 >(488, 160, 544, 184), NULL, NewGameButton, L"New", L"Create new game");
	menuGuienv->addButton(rect< s32 >(488, 192, 544, 216), NULL, LoadGameButton, L"Load", L"Loads selected game");
	menuGuienv->addButton(rect< s32 >(488, 224, 544, 248), NULL, DeleteGameButton, L"Delete", L"Deletes selected game");

	menuGuienv->addButton(rect< s32 >(488, 224, 544, 248), NULL, QuitMenuButton, L"Quit", L"Exits editor");

	for (u32 i=0; i<EGDC_COUNT ; ++i)
	{
		SColor color = menuGuienv->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		color.setAlpha(255);
		menuGuienv->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, color);
	}


	/*
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
	*/
}

void Universe::EditorGUIInit()
{
	guienv = render->device->getGUIEnvironment();
	render->device->setEventReceiver((IEventReceiver*)editorEventReceiver);

	IGUIWindow* wnd = guienv->addWindow(rect< s32 >(0, 0, toolbarWidth, screenHeight), false, L"Toolbar", 0, ToolBarWindow);
	
	//IGUIButton* btn = guienv->addButton(rect< s32 >(10, 128, 110, 128 + 32), wnd, QuitEditorButton, L"Quit", L"Exits to main menu");
	
	//Floors ComboBox
	IGUIComboBox* floorsComboBox = guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 32, toolbarLeftMargin + 176, 48), wnd, FloorsComboBox);
	floorsComboBox->addItem(L"outside");
	floorsComboBox->addItem(L"first fl.");
	
	//Locations ComboBox
	locationsComboBox = guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 64, toolbarLeftMargin + 176, 80), wnd, LocationsComboBox);
	for (int i = 0; i < game->data->locationsCount; i++)
	{
		wchar_t* wstr = strToWchart(game->data->locations[i]->name);
		locationsComboBox->addItem(wstr);
		delete wstr;
	}

	//MapObject select windows, tabs, buttons, etc.
	IGUITabControl* tabc = guienv->addTabControl(rect< s32 >(toolbarLeftMargin, 92, toolbarLeftMargin + 176, 92 + 256), wnd, true, true, MapObjectsTabControl);
	IGUITab* tab;
	for (int i = 0; i < 5; i++)
	{
		tab = tabc->addTab(L"MO", i + MapCellSelectWindowTab);
		guienv->addButton(rect< s32 >(16, 16, 64, 32), tab, i + MapCellSelectWindowToggleButton, L"Select", L"Select MapObject from list");
	}
	
	//Brush mask scroll bar
	IGUIScrollBar* sb = guienv->addScrollBar(true, rect< s32 >(8, 64, 168, 80), tabc->getTab(0), BrushMaskSizeScroll);
	sb->setMax(10);
	sb->setMin(1);
	sb->setPos(3);
	//guienv->addSpinBox(L"asd", rect< s32 >(toolbarLeftMargin, 432, toolbarLeftMargin + 176, 464), true, wnd);

	IGUIStaticText* lbl = guienv->addStaticText(L"3x", rect< s32 >(8, 88, 168, 104), false, false, tabc->getTab(0), BrushMaskSizeStaticText, true);

	wnd->setDraggable(false); //TEST
	wnd->getCloseButton()->setEnabled(false); //TEST

	//gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
	gui::IGUIFont* font2 = render->device->getGUIEnvironment()->getFont("editor/font.bmp");
	guienv->getSkin()->setFont(font2);
}

void Universe::MenuGUIDestroy()
{
	menuGuienv->clear();
}

void Universe::EditorGUIDestroy()
{
	guienv->clear();
}

void Universe::CameraMove(int x, int y)
{
	if ((cameraX + x) < 0 || ((cameraX + x) + screenWidth - toolbarWidth) >= currentLocation->width * CELL_SIZE)
		x = 0;
	if ((cameraY + y) < 0 || ((cameraY + y) + screenHeight) >= currentLocation->height * CELL_SIZE)
		y = 0;
	cameraX += x;
	cameraY += y;
	//Sleep(8);
}

void Universe::DrawScene()
{
	int i, j, drawWidth, drawHeight;

	//for (i = 0; i < currentLocation->height; i++)
	for (i = 0; i < currentLocation->height; i++)
	{
		//for (j = 0; j < currentLocation->width; j++)
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j]->cellProperty)
			{
				case Free:
					render->drawKub(j*CELL_SIZE,-20,i*CELL_SIZE);
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

bool Universe::Menu()
{
	Universe::instance->gameName = NULL;

	MenuGUIInit();
	
	state = Continue;
	while (render->device->run() && state == Continue)
	{
		render->driver->beginScene(true, true, SColor(255, 100, 101, 140));
			menuGuienv->drawAll();
		render->driver->endScene();
	}

	MenuGUIDestroy();

	if (Universe::instance->gameName)
		return false;

	return true;
}

bool Universe::Run()
{
	game = new Game(gameName, Editor);
	SetLocation(game->data->locations[0]);

	BrushesInit();
	
	EditorGUIInit();
	
	CreateBrushMask(1); //TODO: slider get value
	
	int lastUpdate = SDL_GetTicks();

	//DrawScene();
	//render->smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
	
	//render->smgr->addCameraSceneNodeFPS();
	ICameraSceneNode *camera=render->smgr->addCameraSceneNode(0, vector3df(50,50,10), vector3df(50,0,40));
	//render->device->getCursorControl()->setVisible(false);
	/* //Uncomment it (and comment two lines above) to enable gui control
	//render->smgr->addCameraSceneNodeFPS();
	render->device->getCursorControl()->setVisible(true);
	*/

	DrawScene();
	render->drawKub(0,0,0);
	state = Continue;
	while (render->device->run() && state == Continue)
	{
		//core::vector3df<f32> Km = camera->getPosition();
		//core::p
		//core::vector2df<f32> m = render->device->getCursorControl()->getPosition();
		if(editorEventReceiver->IsKeyDown(irr::KEY_LEFT))
		{
			//Km.X-=2;
		}
		//camera->setPosition(Km)

		render->driver->beginScene(true, true, SColor(255,100,101,140));
			render->smgr->drawAll();
			guienv->drawAll();
		render->driver->endScene();
	}

	EditorGUIDestroy();

	for (int i = 0; i < brushesCount; i++)
		delete brushMasks[i];
	delete brushMasks;

	delete game;

	if (state == NextLevel)
		return false;
	return true;
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
}
