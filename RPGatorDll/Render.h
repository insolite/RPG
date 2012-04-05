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
	static Render* instance;
	//irrlicht
	IrrlichtDevice *device;
	IVideoDriver* driver ;
    ISceneManager* smgr;

	//Universe* universe = Universe::instance;

	__declspec(dllexport) void drawScene();
	__declspec(dllexport) void createMenu();
	__declspec(dllexport) void drawKub(f32 xPos,f32 yPos,f32 zPos);
	__declspec(dllexport) ISceneNode* createNode(bool isMD2, char* model, char* texture = NULL, bool light=false,core::vector3df scale=core::vector3df(1, 1, 1), core::vector3df pos=core::vector3df(0, 0, 0), core::vector3df rotation=core::vector3df(0, 0, 0));
	__declspec(dllexport) void moveNode(ISceneNode* node/*dolgno prokotit*/,core::vector3df nextpos);
	__declspec(dllexport) vector3df mouseToUniverse();


	__declspec(dllexport) int getAngle(int x1, int y1, int x2, int y2, bool norm = true);

	__declspec(dllexport) Render(int screenWidth, int screenHeight, wchar_t* windowTitle);
	__declspec(dllexport) ~Render(void);
};
