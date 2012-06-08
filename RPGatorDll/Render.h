#pragma once
#include "ForwardDeclaration.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

enum
{
	ID_IsNotPickable = 0,
	IDFlag_IsPickable = 1 << 0
};

class __declspec(dllexport) Render
{
public:
	static Render* instance;
	IrrlichtDevice *device;
	IVideoDriver* driver;
    ISceneManager* smgr;
	int screenWidth, screenHeight; //pixels
	core::vector3df Kt;
	core::vector3df Km;
	CAnimationEndCallBack* animationEndCallBack;

	void drawKub(f32 xPos,f32 yPos,f32 zPos,int Wid, int Hei);
	ISceneNode* createNode(bool isMD2, IAnimatedMesh* mesh, ITexture* material = NULL, bool light=false, core::vector3df scale=core::vector3df(1, 1, 1), core::vector3df pos=core::vector3df(0, 0, 0), core::vector3df rotation=core::vector3df(0, 90, 0));
	void moveNode(ISceneNode* node,core::vector3df nextpos, f32 speed);
	vector2d<f32> MouseCoordToWorldCoord();
 	template<class T>
	T* GetCurrentMapObjectUnderCursor(T** currentMapObjects, int currentMapObjectsCount)
	{
		vector3df mousePosition3D;
		line3df ray2 = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(device->getCursorControl()->getPosition(), smgr->getActiveCamera());
		plane3df plane(vector3df(0, 0, 0), vector3df(0, -1, 0));
		plane.getIntersectionWithLine(ray2.start, ray2.getVector(), mousePosition3D);

		ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
		
		line3d<f32> ray;
		ray.start = smgr->getActiveCamera()->getAbsolutePosition();
		ray.end = ray.start + (mousePosition3D - ray.start).normalize() * 1000.0f;
		
		vector3df intersection;
		triangle3df hitTriangle;

		ISceneNode* selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, IDFlag_IsPickable, 0);
		if (selectedSceneNode)
			for (int i = 0; i < currentMapObjectsCount; i++)
				if (selectedSceneNode == currentMapObjects[i]->node)
					return currentMapObjects[i];
		return NULL;
	}

	double GetAngle(double x1, double y1, double x2, double y2);
	dimension2d<u32> GetDesktopRes();

	void PlayEffect(ISceneNode* p, core::array< video::ITexture* > textures);

	void Effect2(core::vector3df s,  core::vector3df f);

	Render(int screenWidth, int screenHeight, bool fullscreen, wchar_t* windowTitle);
	~Render(void);
};
