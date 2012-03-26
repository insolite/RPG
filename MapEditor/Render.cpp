#include "StdAfx.h"
#include "Render.h"


Render::Render(int screenWidth, int screenHeight)
{
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 16, false, false, false, 0);

	if (!device)
		return;
	device->setWindowCaption(L"RPGator");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();		
}


Render::~Render(void)
{
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