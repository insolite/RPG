#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Render.h"

Render* Render::instance = NULL;

Render::Render(int screenWidth, int screenHeight, wchar_t* windowTitle)
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 16, false, false, false, NULL); //(IEventReceiver*)editorEventReceiver
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

void Render::drawScene()
{

}

void Render::createMenu()
{

}

void Render::drawKub(f32 xPos,f32 yPos,f32 zPos)
{
	ISceneNode* n = smgr->addCubeSceneNode(); // создаем на сцене куб
        if (n)
        {
				n->setPosition(core::vector3df(xPos,yPos,zPos)); // позиционирем сферу
                n->setMaterialTexture(0, driver->getTexture("grass.bmp")); // текстурируем куб
                n->setMaterialFlag(video::EMF_LIGHTING, false); // отключаем обработку освещения
				//n->scal
        }
}

ISceneNode* Render::createNode(bool isMD2, char* model, char* texture, bool light,core::vector3df scale, core::vector3df pos, core::vector3df rotation)
{
	IAnimatedMesh* mesh = smgr->getMesh(model);
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if(node)
	{
		node->setPosition(pos);
		node->setRotation(rotation);
		node->setScale(scale);
		node->setAnimationSpeed(20.f);

		if(isMD2)
		{
			//node->setMD2Animation(scene::EMAT_POINT); //or interval of frame for scelet animation
			//node->setAnimationSpeed(20.f);
			video::SMaterial material;
			material.setTexture(0, driver->getTexture(texture));
			material.Lighting = light;
			//material.NormalizeNormals = true;// on future
			node->getMaterial(0) = material;
		}
		else
		{
			//
			//...
		}
	}

	return node;
}

void Render::moveNode(ISceneNode* node/*dolgno prokotit*/,core::vector3df nextpos)
{
	scene::ISceneNodeAnimator* anim =
		smgr->createFlyStraightAnimator(node->getPosition(), nextpos, 10000/*тут швидкість має рахуватись динамічно, взалежності від відстані і т п..*/);
                if (anim)
                {
                        node->addAnimator(anim);
                        anim->drop();
                }
}