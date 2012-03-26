#include "StdAfx.h"
#include "Render.h"


Render::Render(void)
{
	//universe = Universe::instance;
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