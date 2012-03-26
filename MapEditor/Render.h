#pragma once
//#include "stdafx.h"
//#include "Universe.h"
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Render
{
public:
	Render(void);
	~Render(void);

	//irrlicht
	IrrlichtDevice *device;
	IVideoDriver* driver ;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;

	//Universe* universe = Universe::instance;

	void drawScene();
	void createMenu();
	void drawKub(f32 xPos,f32 yPos,f32 zPos);
};

