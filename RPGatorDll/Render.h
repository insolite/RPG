#pragma once
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

class Render
{
public:
	//irrlicht
	IrrlichtDevice *device;
	IVideoDriver* driver ;
    ISceneManager* smgr;

	//Universe* universe = Universe::instance;

	__declspec(dllexport) void drawScene();
	__declspec(dllexport) void createMenu();
	__declspec(dllexport) void drawKub(f32 xPos,f32 yPos,f32 zPos);

	__declspec(dllexport) Render(int screenWidth, int screenHeight, wchar_t* windowTitle);
	__declspec(dllexport) ~Render(void);
};
