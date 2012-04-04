#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Render.h"

Render::Render(int screenWidth, int screenHeight, wchar_t* windowTitle)
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(screenWidth, screenHeight), 16, false, false, false, NULL); //(IEventReceiver*)editorEventReceiver
	device->setResizable(true);
	if (!device)
		return;
	device->setWindowCaption(windowTitle);

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	
	
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