#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentNPC.h"
#include "CurrentStatic.h"
#include "CurrentItem.h"
#include "CurrentCharacter.h"
#include "Location.h"
#include "GameData.h"
#include "Game.h"
#include "CAnimationEndCallBack.h"
#include "FlyStraightWCallBackAnimator.h"
#include "Render.h"

Render* Render::instance = NULL;

Render::Render(int screenWidth, int screenHeight, bool fullscreen, wchar_t* windowTitle)
{
	dimension2d<u32> screenRes;

	screenRes = GetDesktopRes();
	this->screenWidth = screenRes.Width;
	this->screenHeight = screenRes.Height;

	//this->screenWidth = screenWidth;
	//this->screenHeight = screenHeight;
	//screenRes = dimension2d<u32>(screenWidth, screenHeight);

	device = createDevice(video::EDT_OPENGL, screenRes, 32, fullscreen, false, false, NULL);
	device->setResizable(true);
	if (!device)
		return;
	device->setWindowCaption(windowTitle);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	
	animationEndCallBack = new CAnimationEndCallBack();

	instance = this;
}

Render::~Render(void)
{
	device->drop();
	instance = NULL;
}

void Render::drawKub(f32 xPos, f32 yPos, f32 zPos, int width, int height)
{
	//int cell= Universe::instanse->
	//IMeshSceneNode* n = smgr->addCubeSceneNode(10,0,-1,vector3df(xPos, yPos, zPos),vector3df(0,0,0),vector3df(Wid, 1, Hei));
	//IMeshSceneNode* n = smgr->addMeshSceneNode(smgr->getMesh("Cube_1.3ds"));
	//IMeshSceneNode* n = smgr->addMeshSceneNode(smgr->getMesh("house_1.x"));
	//n=smgr->addHillPlaneMesh("",dimension2d<f32>(10,10),dimension2d<f32>(64,64),0,1);
	//n=smgr->create
	//if (n)
		//n->setScale(vector3df(Wid, 1, Hei));
		//n->setScale(vector3df(3, 3, 3));
		//n->setPosition(core::vector3df(xPos, yPos, zPos));
		//smgr->getMeshManipulator()->makePlanarTextureMapping(
		//n->setMaterialTexture(0, driver->getTexture("grass.bmp"));
		//n->setMaterialTexture(0, driver->getTexture("ScotsPineTrunk.TGA"));
		//n->setMaterialTexture(0, driver->getTexture("house.png"));
		//n->setMaterialFlag(video::EMF_LIGHTING,false);
		//n->addShadowVolumeSceneNode();
		//n->setID(ID_IsNotPickable);
	//}
	// add terrain scene node
        scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
                "heith.bmp",
                0,                                      // parent node
                -1,                                     // node id
                core::vector3df(0.f, 0.f, 0.f),         // position
                core::vector3df(0.f, 0.f, 0.f),         // rotation
                core::vector3df(20.f, 1.0f, 20.f),      // scale
                video::SColor ( 255, 255, 255, 255 ),   // vertexColor
                5,                                      // maxLOD
                scene::ETPS_17,                         // patchSize
                4                                       // smoothFactor
                );

        //terrain->setMaterialFlag(video::EMF_LIGHTING, false);

        terrain->setMaterialTexture(0,
                        driver->getTexture("terrain-texture.jpg"));
        terrain->setMaterialTexture(1,
                        driver->getTexture("Grass.jpg"));
        
        terrain->setMaterialType(video::EMT_DETAIL_MAP);

        terrain->scaleTexture(1.0f, 100.0f);
}

ISceneNode* Render::createNode(bool isMD2, IAnimatedMesh* mesh, ITexture* texture, bool light,core::vector3df scale, core::vector3df pos, core::vector3df rotation)
{
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh, NULL, IDFlag_IsPickable);
	
	if(node)
	{
		node->setPosition(pos);
		node->setRotation(rotation);
		node->setScale(scale);
		node->setAnimationSpeed(20.f);
		scene::ITriangleSelector* selector = 0;
		selector = smgr->createTriangleSelector(node);
		node->setTriangleSelector(selector);
		selector->drop();
		
		//Autoscale
		f32 scale = 0.25f;
		node->setScale(vector3df(scale,scale,scale));
		
		if (texture)
		{
			//node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMaterialTexture(0, texture);
		}

		node->setMD2Animation(EMAT_STAND);
	}

	return node;
}

void Render::moveNode(ISceneNode* node, core::vector3df nextpos)
{
	vector3df oldPosition = node->getPosition();
	int duration = (int)(30 * sqrt(pow(oldPosition.X - nextpos.X, 2) + pow(oldPosition.Z - nextpos.Z, 2)));
	//scene::ISceneNodeAnimator* anim = smgr->createFlyStraightAnimator(node->getPosition(), nextpos, duration);
	scene::ISceneNodeAnimator* anim = new FlyStraightWCallBackAnimator(node->getPosition(), nextpos, duration, false, device->getTimer()->getTime());
	((FlyStraightWCallBackAnimator*)anim)->setAnimatorEndCallBack(Render::instance->animationEndCallBack);
	vector3df rot(0.0f, (f32)GetAngle(oldPosition.X, oldPosition.Z, nextpos.X, nextpos.Z), 0.0f);
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
	
	return -(int)angle;
}

vector3df Render::MouseCoordToWorldCoord()
{
	core::vector3df pos;

	line3df ray2 = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(device->getCursorControl()->getPosition(), smgr->getActiveCamera());
	core::plane3df plane = plane3df(vector3df(0, -15, 0), vector3df(0, -1, 0));
    if (!plane.getIntersectionWithLine(ray2.start, ray2.getVector(), pos))
		printf("ray does not intersect the plane!");
	return pos;
}

dimension2d<u32> Render::GetDesktopRes()
{
	IrrlichtDevice * device0 = 0;
	dimension2d<u32> DesktopResolution;
	device0 = createDevice(EDT_NULL, dimension2d<u32>(100, 100), false, false);
	video::IVideoModeList * list = device0->getVideoModeList();
	DesktopResolution = list->getDesktopResolution();
	device0->drop();
	return DesktopResolution;
}

void Render::PlayEffect(ISceneNode* p, core::array< video::ITexture* > textures)
{
	scene::IVolumeLightSceneNode * n = smgr->addVolumeLightSceneNode(0, -1,
                                32,                              // Subdivisions on U axis
                                32,                              // Subdivisions on V axis
                                video::SColor(0, 255, 255, 255), // foot color
                                video::SColor(0, 0, 0, 0));      // tail color

        if (n)
        {
			n->setParent(p);
            n->setScale(core::vector3df(56.0f, 56.0f, 56.0f));
            //n->setPosition(core::vector3df(-120,50,40));

             scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures, 92, false);
			 
			 //((IAnimatedMeshSceneNode*)n)->setAnimationEndCallback(animationEndCallBack);
             n->addAnimator(glow);
			 
             glow->drop();
        }
}

void Render::Effect2(core::vector3df s,  core::vector3df f)
{
        scene::ISceneNode* light2 =
                smgr->addLightSceneNode(0, core::vector3df(0,0,0),
                video::SColorf(1.0f, 0.2f, 0.2f, 0.0f), 800.0f);

        scene::ISceneNodeAnimator* anim =
                        smgr->createFlyStraightAnimator(s, f, 3500, true);
        light2->addAnimator(anim);
        anim->drop();

        scene::ISceneNode* bill = smgr->addBillboardSceneNode(light2, core::dimension2d< f32 >(120, 120));
        bill->setMaterialFlag(video::EMF_LIGHTING, false);
        bill->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        bill->setMaterialTexture(0, driver->getTexture("particlewhite.bmp"));

        scene::IParticleSystemSceneNode* ps =
                smgr->addParticleSystemSceneNode(false, light2);

        scene::IParticleEmitter* em = ps->createBoxEmitter(
                core::aabbox3d< f32 >(-3,0,-3,3,1,3),
                core::vector3df(0.0f,0.03f,0.0f),
                80,100,
                video::SColor(0,255,255,255), video::SColor(0,255,255,255),
                400,1100);
        em->setMinStartSize(core::dimension2d< f32 >(30.0f, 40.0f));
        em->setMaxStartSize(core::dimension2d< f32 >(30.0f, 40.0f));

        ps->setEmitter(em);
        em->drop();

        scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();
        ps->addAffector(paf);
        paf->drop();

        ps->setMaterialFlag(video::EMF_LIGHTING, false);
        ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        ps->setMaterialTexture(0, driver->getTexture("fireball.bmp"));
        ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}
