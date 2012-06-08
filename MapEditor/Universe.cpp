#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "MenuEventReceiver.h"
#include "EditorEventReceiver.h"
#include "Universe.h"

Universe* Universe::instance;

Universe::Universe(void)
{
	cameraMoveZoneWidth = 24;
	toolbarWidth = 192;
	toolbarLeftMargin = 8;
	brushMaskMinSize = 1;
	brushMaskMaxSize = 10;
	instance = this;

	render = new Render(1366, 768, true, L"RPGator");

	guienv = render->device->getGUIEnvironment();

	gui::IGUIFont* font2 = guienv->getFont("res/font.xml");
	guienv->getSkin()->setFont(font2);
	
	SColor color;

	color = guienv->getSkin()->getColor(EGDC_3D_FACE);
	color.setAlpha(208);
	guienv->getSkin()->setColor(EGDC_3D_FACE, color);
	
	color = guienv->getSkin()->getColor(EGDC_3D_SHADOW);
	color.setAlpha(208);
	guienv->getSkin()->setColor(EGDC_3D_SHADOW, color);
}

Universe::~Universe(void)
{
	delete menuEventReceiver;
	delete editorEventReceiver;
	delete render;
	instance = NULL;
}

void Universe::MenuGUIInit()
{
	menuEventReceiver = new MenuEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)menuEventReceiver);

	char** games;
	int gamesCount;
	wchar_t wstr[512];
	gamesCount = ReadDir("editor", games, true);
	IGUIListBox* lb = guienv->addListBox(rect< s32 >(256, 160, 480, 512), NULL, GamesListBox, true);
	for (int i = 0; i < gamesCount; i++)
	{
		mbstowcs(wstr, games[i], 255);
		lb->addItem(wstr);
		delete games[i];
	}
	delete games;
	if (lb->getItemCount() > 0)
		lb->setSelected(0);
	
	guienv->addButton(rect< s32 >(488, 160, 544, 184), NULL, NewGameButton, L"New", L"Create new game");
	guienv->addButton(rect< s32 >(488, 192, 544, 216), NULL, LoadGameButton, L"Load", L"Loads selected game");
	guienv->addButton(rect< s32 >(488, 224, 544, 248), NULL, DeleteGameButton, L"Delete", L"Deletes selected game");
	guienv->addButton(rect< s32 >(488, 256, 544, 280), NULL, QuitMenuButton, L"Quit", L"Exits editor");
}

void Universe::EditorGUIInit()
{
	editorEventReceiver = new EditorEventReceiver();
	render->device->setEventReceiver((IEventReceiver*)editorEventReceiver);

	IGUIWindow* wnd = guienv->addWindow(rect< s32 >(0, 0, toolbarWidth, render->screenHeight), false, L"Toolbar", 0, ToolBarWindow);
	
	//Floors ComboBox
	IGUIComboBox* floorsComboBox = guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 32, toolbarLeftMargin + 176, 48), wnd, FloorsComboBox);
	floorsComboBox->addItem(L"outside");
	floorsComboBox->addItem(L"first fl.");
	
	//Locations ComboBox
	IGUIComboBox* locationsComboBox = guienv->addComboBox(rect< s32 >(toolbarLeftMargin, 64, toolbarLeftMargin + 160, 80), wnd, LocationsComboBox);
	wchar_t wstr[512];
	for (int i = 0; i < game->data->locationsCount; i++)
	{
		mbstowcs(wstr, game->data->locations[i]->name, 255);
		locationsComboBox->addItem(wstr);
	}

	//Locations control buttons
	IGUIButton* b = guienv->addButton(rect< s32 >(toolbarLeftMargin + 128 + 32, 64, toolbarLeftMargin + 128 + 48, 80), wnd, LocationsEditButton, L"*", L"Edit locations");
	b->setIsPushButton(true);

	//MapObject select windows, tabs, buttons, etc.
	IGUITabControl* tabc = guienv->addTabControl(rect< s32 >(toolbarLeftMargin, 92, toolbarLeftMargin + 176, 92 + 256 + 32), wnd, true, true, MapObjectsTabControl);
	IGUITab* tab;
	wchar_t* wstrs[5] = { L"C", L"N", L"S", L"I", L"C" };
	for (int i = 0; i < 5; i++)
	{
		tab = tabc->addTab(wstrs[i], -1);
		guienv->addButton(rect< s32 >(8, 8, 8 + 70, 8 + 32), tab, MapObjectSelectWindowToggleButton, L"Select", L"Select MapObject from list");
		guienv->addButton(rect< s32 >(8 + 70 + 8, 8, 8 + 70 + 8 + 70, 8 + 32), tab, MapObjectAddButton, L"Add", L"Add MapObject to list");
		CGUIMeshViewer* mv = new CGUIMeshViewer(guienv, tab, MapObjectTabPreview, rect< s32 >(8, 8 + 32 + 16, 8 + 70 + 8 + 70, 8 + 70 + 16 + 128));
		SMaterial* sm = new SMaterial();
		sm->setTexture(0, brush[i]->texture);
		sm->setFlag(EMF_LIGHTING, false);
		mv->setMesh(brush[i]->mesh);
		mv->setMaterial(*sm);
		mv->drop();
	}
	tabc->setActiveTab(1);
	/*
	//Brush mask ScrollBar and StaticText
	IGUIScrollBar* sb = guienv->addScrollBar(true, rect< s32 >(8, 64, 168, 80), tabc->getTab(0), BrushMaskSizeScroll);
	sb->setMax(10);
	sb->setMin(1);
	sb->setPos(3);
	guienv->addStaticText(L"3x", rect< s32 >(8, 88, 168, 104), false, false, tabc->getTab(0), BrushMaskSizeStaticText, true);
	*/
	wnd->setDraggable(false); //TEST
	wnd->getCloseButton()->setEnabled(false); //TEST
	wnd->getCloseButton()->setVisible(false); //TEST
}

void Universe::MenuGUIDestroy()
{
	guienv->clear();
	render->device->setEventReceiver(NULL);
	delete menuEventReceiver;
}

void Universe::EditorGUIDestroy()
{
	guienv->clear();
	render->device->setEventReceiver(NULL);
	delete editorEventReceiver;
}

void Universe::DrawScene()
{
	/*
	//for (i = 0; i < currentLocation->height; i++)
	for (i = 0; i < currentLocation->height; i++)
	{
		//for (j = 0; j < currentLocation->width; j++)
		for (j = 0; j < currentLocation->width; j++)
		{
			switch (currentLocation->mask[i][j]->cellProperty)
			{
				case Free:
					render->drawKub(j*CELL_SIZE*9.9,-20,i*CELL_SIZE*9.9,1,1);
					break;
				//case Locked:
					//glColor4d(1, 0, 0, 0.5);
					//break;
				//default:
				//	glColor4d(1, 1, 1, 1);
			}
		}
	}//*/
	render->drawKub(0,-20,0,currentLocation->width,currentLocation->height);

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
			guienv->drawAll();
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
	
	DrawScene();
	//variables for camera
	camPos=render->smgr->addEmptySceneNode();
	camPos->setPosition(vector3df(50,50,10));
	camera=render->smgr->addCameraSceneNode(0, vector3df(50,50,10), vector3df(50,0,40));

	scene::ISceneNode* lnode; 
	lnode = render->smgr->addLightSceneNode(0,vector3df(0,30,0),video::SColorf(1.0f, 1.0f, 1.0f, 1.0f),800.0F);
	render->smgr->setAmbientLight(video::SColor(0,60,60,60));
	
	camPos->setID(ID_IsNotPickable);
	camera->setID(ID_IsNotPickable);
	
	cameraY = 50;

	state = Continue;

	int lastUpdate = render->device->getTimer()->getTime();

	while (render->device->run() && state == Continue)
	{
		render->Km = camPos->getPosition();
		render->Kt = camera->getTarget();
			
		if (editorEventReceiver->IsKeyDown(KEY_LEFT))
		{
			render->Kt.X -= CAMERA_STEP;
			render->Km.X -= CAMERA_STEP;
			camPos->setPosition(render->Km);
		}
		if (editorEventReceiver->IsKeyDown(KEY_RIGHT))
		{
			render->Kt.X += CAMERA_STEP;
			render->Km.X += CAMERA_STEP;
			camPos->setPosition(render->Km);
		}
		if (editorEventReceiver->IsKeyDown(KEY_UP))
		{
			render->Kt.Z += CAMERA_STEP;
			render->Km.Z += CAMERA_STEP;
			camPos->setPosition(render->Km);
		}
		if (editorEventReceiver->IsKeyDown(KEY_DOWN))
		{
			render->Kt.Z -= CAMERA_STEP;
			render->Km.Z -= CAMERA_STEP;
			camPos->setPosition(render->Km);
		}

		render->Km.Y = cameraY;

		camera->setPosition(render->Km);
		camera->setTarget(render->Kt);
		
		//vector3df lPos = camera->getPosition();
		vector3df lPos = render->Kt;
		lPos.Y = 15;
		//lPos.Z += 20;
		lnode->setPosition(lPos);


		if ((render->device->getTimer()->getTime() - lastUpdate) > 30)
		{
			//OMG, performance is too high :)
			lastUpdate = render->device->getTimer()->getTime();
			
			render->driver->beginScene(true, true, SColor(255,100,101,140));
				render->smgr->drawAll();
				guienv->drawAll();
			render->driver->endScene();
		}
	}
	render->smgr->clear();

	EditorGUIDestroy();

	delete game;

	if (state == NextLevel)
		return false;
	return true;
}

void Universe::BrushesInit()
{
	brush[0] = game->resources->mapCells[1];
	brush[1] = game->resources->npcs[0];
	brush[2] = game->resources->statics[0];
	brush[3] = game->resources->items[0];
	brush[4] = game->resources->characters[0];
	
	brushIndex = 0;
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
		y = (int)sqrt((double)(brushRadius * brushRadius - i * i));
		
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
