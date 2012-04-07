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

	__declspec(dllexport) void drawKub(f32 xPos,f32 yPos,f32 zPos,int Wid, int Hei);
	__declspec(dllexport) ISceneNode* createNode(bool isMD2, IAnimatedMesh* mesh, ITexture* material = NULL, bool light=false, core::vector3df scale=core::vector3df(1, 1, 1), core::vector3df pos=core::vector3df(0, 0, 0), core::vector3df rotation=core::vector3df(0, 0, 0));
	__declspec(dllexport) void moveNode(ISceneNode* node,core::vector3df nextpos);
	__declspec(dllexport) vector3df MouseCoordToWorldCoord();
	__declspec(dllexport) ISceneNode* Render::getNodeUnderCursor(int id);

	__declspec(dllexport) int GetAngle(int x1, int y1, int x2, int y2);

	__declspec(dllexport) Render(int screenWidth, int screenHeight, bool fullscreen, wchar_t* windowTitle);
	__declspec(dllexport) ~Render(void);
};
