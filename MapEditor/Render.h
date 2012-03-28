#pragma once

class Render
{
public:
	Render(int screenWidth, int screenHeight);
	~Render(void);

	//irrlicht
	IrrlichtDevice *device;
	IVideoDriver* driver ;
    ISceneManager* smgr;

	//Universe* universe = Universe::instance;

	void drawScene();
	void createMenu();
	void drawKub(f32 xPos,f32 yPos,f32 zPos);
};
