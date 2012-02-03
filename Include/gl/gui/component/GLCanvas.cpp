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
#include "./GLCanvas.h"

#include "../Config.h"
#include "../Graphics.h"

namespace ui
{

	GLCanvas::GLCanvas()
	{
		init(250,250);
	}

	GLCanvas::GLCanvas(int width, int height)
	{
		init(width,height);
	}

	void GLCanvas::init(int width, int height)
	{
		setViewportWidth(width);
		setViewportHeight(height);
		setThemeName("GLCanvas");
	}

	void GLCanvas::setViewportHeight(int h)
	{
		height = h;
	}

	void GLCanvas::setViewportWidth(int w)
	{
		width = w;
	}

	int GLCanvas::getViewportWidth() const
	{
		return width;
	}

	int GLCanvas::getViewportHeight() const
	{
		return height;
	}

	void GLCanvas::paintSelectionComponent(Graphics &g)
	{
						int x = getLocationOnScreen().x;
				int y = getLocationOnScreen().y;
				int width = getBounds().width;
				int height = getBounds().height;

				g.enableScissor(x,y,width,height);

				// GL_ALL_ATTRIB_BITS - better?
				//glPushAttrib(GL_VIEWPORT_BIT);
				glPushAttrib(GL_ALL_ATTRIB_BITS);

				//int viewport[4];
				GLint viewport[4];
				glGetIntegerv(GL_VIEWPORT,viewport);

				// adjust from OpenGL coordinate system to ours..
				y = viewport[3] - y - height;

				// enter projection mode
				glMatrixMode(GL_PROJECTION);

				// save current projection matrix
				glPushMatrix();

				// reset coordinate system
				glLoadIdentity();

				// adjust viewport
				glViewport(x,y,width,height);

				// set perspective
				gluPerspective(45,1*(width/height),1,1000);

				// set to modelview mode
				glMatrixMode(GL_MODELVIEW);

				// reset coordinate system
				glLoadIdentity();

				// point 'camera'
				gluLookAt(0.0,0.0,5.0,0.0,0.0,-1.0,0.0f,1.0f,0.0f);

				glClear(GL_DEPTH_BUFFER_BIT);

				// call pure render function
				//canvas->render();
				renderSelection();
				//Component::paintSelectionComponent(g);

				// switch to projection
				glMatrixMode(GL_PROJECTION);

				// pop, restoring the old projection matrix
				glPopMatrix();

				// reset modelview matrix
				glMatrixMode(GL_MODELVIEW);

				// restore viewport
				glPopAttrib();

				g.disableScissor();
		 
	}

}