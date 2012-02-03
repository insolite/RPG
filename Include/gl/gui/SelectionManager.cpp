/*
 * Copyright (c) 2003-2006, Bram Stein
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 *  2. Redistributions in binary form must reproduce the above copyright 
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution. 
 *  3. The name of the author may not be used to endorse or promote products 
 *     derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO 
 * EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "./SelectionManager.h"
#include "./Graphics.h"
#include "./Component.h"
#include "./event/MouseEvent.h"
#include "./FocusManager.h"

namespace ui
{
	int SelectionManager::getRenderMode() const
	{
		return mode;
	}

	void SelectionManager::setRenderMode(int m)
	{
		// you have specified an invalid render mode.
		assert(m == NORMAL || m == SELECTION);

		mode = m;
	}

	void SelectionManager::beginUpdate(int x, int y)
	{
		mouseX = x;
		mouseY = y;

	//	if(tempComponent != 0)
	//	{
	//		if(!tempComponent->getBounds().contains(x,y))
	//		{
				tempComponent = getComponentAt(x,y);
	//		}
	//	}
	//	else
	//	{
	//		tempComponent = getComponentAt(x,y);
	//	}
	}

	SelectionManager::SelectionManager()
		:	mouseX(0),
			mouseY(0),
			lastX(0),
			lastY(0),
			foundComponent(0),
			tempComponent(0),
			hoverOverComponent(0),
			pressed(false)
	{

		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
			
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
			
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	SelectionManager::~SelectionManager()
	{
	}

	Component* SelectionManager::getComponentAt(int x, int y) const
	{
		GLint viewport[4];
		GLubyte pixel[3];

		glGetIntegerv(GL_VIEWPORT,viewport);

		glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,static_cast<void *>(pixel));

		std::vector<ColorRegisterValue>::const_iterator iter;

		for(iter = colorRegister.begin(); iter != colorRegister.end(); ++iter)
		{
			if(((*iter).color.red == pixel[0] && (*iter).color.green == pixel[1] && (*iter).color.blue == pixel[2]) ||
				((*iter).textureColor.red == pixel[0] && (*iter).textureColor.green == pixel[1] && (*iter).textureColor.blue == pixel[2]))
			{
				//colorRegister.erase((*iter));
				//break;
				return (*iter).comp;
			}
		}

/*
		for(int i = 0; i < static_cast<int>(pickingList.size()); ++i)
		{
			int index = pickingList[i].first;

			// set seed, and check with the found colors
			srand(index*2);

			int red = (rand() % 255);
			int green =  (rand() % 255);
			int blue = (rand() % 255);
			if((pixel[0] == red) && (pixel[1] == green) && (pixel[2] == blue))
			{
				return pickingList[i].second;
			}
			//if(((pixel[0] - 3) == red) && (pixel[1] == green) && ((pixel[2] - 3) == blue))
			//{
			//	return pickingList[i].second;
			//}
		}
		*/
	//	fprintf(stderr,"%d %d %d\n",pixel[0],pixel[1],pixel[2]);
		return 0;
	}

	
	void SelectionManager::mouseMotion(int x, int y)
	{
		if(foundComponent != 0 && pressed)
		{
			if(lastX == 0 && lastY == 0)
			{
				lastX = x;
				lastY = y;
			}

			int draggedX = x - lastX;
			int draggedY = y - lastY;

			event::MouseEvent dragEvent(foundComponent,event::MouseEvent::MOUSE_DRAGGED,draggedX,draggedY,buttonPressed);
			foundComponent->processMouseEvent(dragEvent);

			lastX = x;
			lastY = y;
		}

		if(foundComponent != 0)
		{
			event::MouseEvent motionEvent(foundComponent,event::MouseEvent::MOUSE_MOTION,x,y,0);
			foundComponent->processMouseEvent(motionEvent);
		}

		

		if(tempComponent != hoverOverComponent)
		{
			if(hoverOverComponent != 0)
			{
				event::MouseEvent exitEvent(hoverOverComponent,event::MouseEvent::MOUSE_EXITED,mouseX,mouseY,0);
				hoverOverComponent->processMouseEvent(exitEvent);
			}

			if(tempComponent != 0)
			{
				// send enter to f
				event::MouseEvent enterEvent(tempComponent,event::MouseEvent::MOUSE_ENTERED,mouseX,mouseY,0);
				tempComponent->processMouseEvent(enterEvent);
			}

			hoverOverComponent = tempComponent;
		}
		else if(tempComponent == 0)
		{
			if(hoverOverComponent != 0)
			{
				event::MouseEvent exitEvent(hoverOverComponent,event::MouseEvent::MOUSE_EXITED,mouseX,mouseY,0);
				hoverOverComponent->processMouseEvent(exitEvent);
			}
		}
	}
	
	void SelectionManager::mousePressed(int button)
	{
		foundComponent = tempComponent;
		
		if(foundComponent != 0)
		{
			event::MouseEvent event(foundComponent,event::MouseEvent::MOUSE_PRESSED,mouseX,mouseY,button);
			foundComponent->processMouseEvent(event);

			// also set focus
			if(foundComponent->hasFocusListener())
				FocusManager::getInstance().setPermanentFocusOwner(foundComponent);
		}
		else
		{
			FocusManager::getInstance().setPermanentFocusOwner(0);
		}
		pressed = true;
		buttonPressed = button;
	}
	
	void SelectionManager::mouseReleased(int button)
	{
		if(foundComponent != 0)
		{
			event::MouseEvent event(foundComponent,event::MouseEvent::MOUSE_RELEASED,mouseX,mouseY,button);
			foundComponent->processMouseEvent(event);

			// check if we're still in the Component by comparing the hoverOverComponent with foundComponent.
			if(foundComponent == hoverOverComponent)
			{
				// yes, we count this as an official click!
				event::MouseEvent mouseClickEvent(foundComponent,event::MouseEvent::MOUSE_CLICKED,mouseX,mouseY,button);
				foundComponent->processMouseEvent(mouseClickEvent);
			}
		}
		pressed = false;
		lastX = 0;
		lastY = 0;
		buttonPressed = -1;
	}

	void SelectionManager::addComponent(Component* comp)
	{
		// check to see if it's already here
		if(getComponentId(comp) == -1)
		{
			ColorRegisterValue val;
			val.index = idCounter;
			val.comp = comp;
		//	pickingList.push_back(std::make_pair<int, Component*>(idCounter,comp));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			glPushAttrib(GL_ALL_ATTRIB_BITS);
			glViewport(0,0,64,64);
			
			glLoadIdentity();

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				gluOrtho2D(0,64,64,0);
				
				//gluOrtho2D(0,800,600,0);

				srand(idCounter*2);

				GLubyte red = rand() % 255;
				GLubyte green = rand() % 255;
				GLubyte blue = rand() % 255;

				glColor3ub(red,green,blue);

				//glColor3f(1.0f,1.0f,0.0f);

				glBegin(GL_QUADS);
			
					glVertex3f(0, 0, 0.0f);	// Top Left
			
					glVertex3f(64, 0, 0.0f);	// Top Right
			
					glVertex3f(64, 64, 0.0f);	// Bottom Right

					glVertex3f(0,64, 0.0f);	// Bottom Left
				glEnd();

				//ui::Frame::paint(g);

			GLubyte pixel[3];

			glReadPixels(10,10,1,1,GL_RGB,GL_UNSIGNED_BYTE,static_cast<void *>(pixel));

			IntegerColor color(pixel[0],pixel[1],pixel[2]);
			
			val.color = color;

			//fprintf(stderr,"glColor: %d %d %d\n",pixel[0],pixel[1],pixel[2]);
			
			glBindTexture(GL_TEXTURE_2D,textureId);
			glCopyTexSubImage2D(GL_TEXTURE_2D,0,0,0,0,0,64,64);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,textureId);

			glBegin(GL_QUADS);

				glTexCoord2f(0.0f,0.0f);
				glVertex3f(0.0f,0.0f,0.0f);
	
				glTexCoord2f(1.0f,0.0f);
				glVertex3f(64.0f,0.0f,0.0f);

				glTexCoord2f(1.0f,1.0f);
				glVertex3f(64.0f,64.0f,0.0f);

				glTexCoord2f(0.0f,1.0f);
				glVertex3f(0.0f,64.0f,0.0f);

			glEnd();

			glDisable(GL_TEXTURE_2D);

			
			glReadPixels(10,10,1,1,GL_RGB,GL_UNSIGNED_BYTE,static_cast<void *>(pixel));
			
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
			
			IntegerColor textureColor(pixel[0],pixel[1],pixel[2]);

			val.textureColor = textureColor;

			//colorRegister[idCounter] = std::make_pair<color,textureColor>;

			//colorRegister.assign(idCounter,std::make_pair<IntegerColor,util::Color>(color,textureColor));

			//fprintf(stderr,"texture: %d %d %d\n\n",pixel[0],pixel[1],pixel[2]);

			//glClear(
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glPopMatrix();
			glPopAttrib();

			colorRegister.push_back(val);

			idCounter++;
		}
	}

	void SelectionManager::removeComponent(Component* comp)
	{
		std::vector<ColorRegisterValue>::iterator iter;

		for(iter = colorRegister.begin(); iter != colorRegister.end(); ++iter)
		{
			if((*iter).comp == comp)
			{
				colorRegister.erase(iter);
				break;
			}
		}

		/*
		std::vector< std::pair<int, Component *> >::iterator iter;

		for(iter = pickingList.begin(); iter != pickingList.end(); ++iter)
		{
			if((*iter).second == comp)
			{
				pickingList.erase(iter);
				break;
			}
		}
		*/
	}

	int SelectionManager::getComponentId(const Component* comp) const
	{
		/*
		for(int i = 0; i < static_cast<int>(pickingList.size()); ++i)
		{
			if(comp == pickingList[i].second)
				return pickingList[i].first;
		}
		*/
		std::vector<ColorRegisterValue>::const_iterator iter;

		for(iter = colorRegister.begin(); iter != colorRegister.end(); ++iter)
		{
			if((*iter).comp == comp)
			{
				return (*iter).index;
			}
		}
		return -1;
	}
}