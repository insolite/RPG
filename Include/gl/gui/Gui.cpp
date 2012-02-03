#include "./Gui.h"
#include "./SelectionManager.h"
#include "./FocusManager.h"
#include "./event/KeyEvent.h"
#include "./event/MouseEvent.h"

namespace ui
{
	Gui::Gui()
	{
		mouseX = mouseY = 0;
	}

	void Gui::addFrame(Frame *frame)
	{
		frameList.push_back(frame);
	}

	void Gui::removeFrame(Frame *frame)
	{
		frameList.erase(std::remove(frameList.begin(),frameList.end(),frame),frameList.end());
	}

	void Gui::paint()
	{
		SelectionManager::getInstance().setRenderMode(SelectionManager::SELECTION);
		SelectionManager::getInstance().mouseMotion(mouseX,mouseY); // for mouse clicks, enter,exit, etc
		std::vector<Frame*>::const_iterator iter;
		for(iter = frameList.begin(); iter != frameList.end(); ++iter)
		{
			(*iter)->paint(g);
		}
		//Container::paint(g); // draw the components a second time.. *sigh*
		SelectionManager::getInstance().beginUpdate(mouseX,mouseY); // for mousemotion
		SelectionManager::getInstance().setRenderMode(SelectionManager::NORMAL);
		
		g.enableBlending();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for(iter = frameList.begin(); iter != frameList.end(); ++iter)
		{
			(*iter)->paint(g);
		}
		//glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
		g.disableBlending();
	
	}

	void Gui::importUpdate(float deltaTime)
	{
		std::vector<Frame*>::const_iterator iter;
		for(iter = frameList.begin(); iter != frameList.end(); ++iter)
		{
			(*iter)->updateComponent(deltaTime);
		}
	}

	void Gui::importMouseMotion(int x, int y)
	{
		if(x == 0 && y == 0)
			return;

		mouseX = x;
		mouseY = y;
	}

	void Gui::importMousePressed(int button)
	{
		// forward it to the pickingmanager
		SelectionManager::getInstance().mousePressed(button);
	}

	void Gui::importMouseReleased(int button)
	{
		// forward it to the pickingmanager
		SelectionManager::getInstance().mouseReleased(button);
	}

	void Gui::importKeyPressed(int keyCode, int modifier)
	{
		FocusManager::getInstance().keyPressed(keyCode,modifier);
	}

	void Gui::importKeyReleased(int keyCode, int modifier)
	{
		FocusManager::getInstance().keyReleased(keyCode,modifier);
	}

	void Gui::setFontFactory(AbstractFontFactory *factory)
	{
		GlyphContext::getInstance().setFontFactory(factory);
	}

	AbstractFontFactory * Gui::getFontFactory() const
	{
		return GlyphContext::getInstance().getFontFactory();
	}
}