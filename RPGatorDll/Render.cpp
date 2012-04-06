#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Render.h"

Render* Render::instance = NULL;

Render::Render(int screenWidth, int screenHeight, bool fullscreen, wchar_t* windowTitle)
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 32, fullscreen, false, false, NULL);
	device->setResizable(true);
	if (!device)
		return;
	device->setWindowCaption(windowTitle);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	
	instance = this;
}

Render::~Render(void)
{
	instance = NULL;
}

void Render::drawKub(f32 xPos, f32 yPos, f32 zPos,int Wid, int Hei)
{
	//int cell= Universe::instanse->
	//IMeshSceneNode* n = smgr->addCubeSceneNode(10,0,-1,vector3df(xPos, yPos, zPos),vector3df(0,0,0),vector3df(Wid, 1, Hei));
	IMeshSceneNode* n = smgr->addCubeSceneNode();
	
	//n=smgr->addP
	if (n)
	{
		n->setScale(vector3df(Wid, 1, Hei));
		n->setPosition(core::vector3df(xPos, yPos, zPos));
		//smgr->getMeshManipulator()->makePlanarTextureMapping(
		n->setMaterialTexture(0, driver->getTexture("grass.bmp"));
		//n->setMaterialFlag(video::EMF_LIGHTING, true);
		//n->addShadowVolumeSceneNode();
	}
}

ISceneNode* Render::createNode(bool isMD2, IAnimatedMesh* mesh, ITexture* texture, bool light,core::vector3df scale, core::vector3df pos, core::vector3df rotation)
{
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if(node)
	{
		node->setPosition(pos);
		node->setRotation(rotation);
		node->setScale(scale);
		node->setAnimationSpeed(20.f);
		if (texture)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMaterialTexture(0, texture);
		}
		/*
		if(isMD2)
		{
			//node->setMD2Animation(scene::EMAT_POINT); //or interval of frame for scelet animation
			//node->setAnimationSpeed(20.f);
			video::SMaterial material;
			material.setTexture(0, driver->getTexture(""));
			material.Lighting = light;
			//material.NormalizeNormals = true;// on future
			node->getMaterial(0) = material;
		}
		else
		{
			//
			//...
		}
		*/
	}

	return node;
}

void Render::moveNode(ISceneNode* node, core::vector3df nextpos)
{
	vector3df oldPosition = node->getPosition();
	int duration = 50 * sqrt(pow(oldPosition.X - nextpos.X, 2) + pow(oldPosition.Z - nextpos.Z, 2));
	scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(node->getPosition(), nextpos, duration);
	vector3df rot(0, GetAngle(oldPosition.X, oldPosition.Z, nextpos.X, nextpos.Z), 0);
	node->setRotation(rot);
	if (anim)
	{
		node->addAnimator(anim);
		anim->drop();
	}
}

int Render::GetAngle(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	double angle = atan((double)dy / (double)dx);
	
	angle *= 180 / M_PI;

	if (dx < 0 && dy >= 0 || dx < 0 && dy <= 0)
		angle += 180.0;
	
	return -angle;
}

vector3df Render::MouseCoordToWorldCoord()
{
	core::vector3df pos;

	line3df ray2 = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(device->getCursorControl()->getPosition(), smgr->getActiveCamera());
	core::plane3df plane = plane3df(vector3df(0, -15, 0), vector3df(0, -1, 0));
    if(plane.getIntersectionWithLine(ray2.start, ray2.getVector(), pos))
		return pos;
	else
		printf("ray does not intersect the plane!");
}
