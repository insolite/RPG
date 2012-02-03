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
#include "./Graphics.h"
#include "./GlyphContext.h"
#include "./Font.h"
#include "./Component.h"

namespace ui
{
/**
 * Constructor/Destructor.
 */
#define FASTGRAPHICS

	Graphics::Graphics(void)
		:	currentPaint(0),
			depth(static_cast<float>(1/Component::NORMAL)),
			transparency(1.0f)
	{
		glEnable(GL_POINT_SMOOTH);
	}

	Graphics::~Graphics(void)
	{
	}

/**
 * Control methods.
 */
	void Graphics::applyCurrentColor()
	{
		//glColor4f(currentColor.red, currentColor.green, currentColor.blue, getCurrentTransparency());
		glColor4f(currentPaint->getRed(0), currentPaint->getGreen(0), currentPaint->getBlue(0), getCurrentTransparency());
	}

	void Graphics::translate(int x, int y)
	{
		if(x != 0 || y != 0)
		{
			glTranslatef(static_cast<GLfloat>(x),static_cast<GLfloat>(y),0);
		}
	}

	void Graphics::popMatrix()
	{
		glPopMatrix();
	}

	void Graphics::pushMatrix()
	{
		glPushMatrix();
	}

	void Graphics::setDepth(float newDepth)
	{
		depth = newDepth;
	}

	float Graphics::getDepth()
	{
		return depth;
	}

//	void Graphics::setColor(const util::Color& color)
//	{
//		currentColor = color;
//	}

	void Graphics::setPaint(const util::Paint* paint)
	{
		currentPaint = paint;
	}


/**
 * Painting
 */
	void Graphics::drawLine(int x1, int y1, int x2, int y2)
	{
		glBegin (GL_LINES);
			glColor4f(currentPaint->getRed(util::Paint::UPPERLEFT),currentPaint->getGreen(util::Paint::UPPERLEFT),currentPaint->getBlue(util::Paint::UPPERLEFT),currentPaint->getAlpha(util::Paint::UPPERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x1),static_cast<GLfloat>(y1),depth);
			glColor4f(currentPaint->getRed(util::Paint::LOWERRIGHT),currentPaint->getGreen(util::Paint::LOWERRIGHT),currentPaint->getBlue(util::Paint::LOWERRIGHT),currentPaint->getAlpha(util::Paint::LOWERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x2),static_cast<GLfloat>(y2),depth);
		glEnd();
	}

	void Graphics::drawRect(int x, int y, int width, int height)
	{
		glBegin(GL_LINE_STRIP);
			glColor4f(currentPaint->getRed(util::Paint::UPPERLEFT),currentPaint->getGreen(util::Paint::UPPERLEFT),currentPaint->getBlue(util::Paint::UPPERLEFT),currentPaint->getAlpha(util::Paint::UPPERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), depth);	// Top Left
			glColor4f(currentPaint->getRed(util::Paint::UPPERRIGHT),currentPaint->getGreen(util::Paint::UPPERRIGHT),currentPaint->getBlue(util::Paint::UPPERRIGHT),currentPaint->getAlpha(util::Paint::UPPERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x+width),static_cast<GLfloat>(y),depth);

			glColor4f(currentPaint->getRed(util::Paint::UPPERRIGHT),currentPaint->getGreen(util::Paint::UPPERRIGHT),currentPaint->getBlue(util::Paint::UPPERRIGHT),currentPaint->getAlpha(util::Paint::UPPERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x + width-1), static_cast<GLfloat>(y), depth);	// Top Right
			glColor4f(currentPaint->getRed(util::Paint::LOWERRIGHT),currentPaint->getGreen(util::Paint::LOWERRIGHT),currentPaint->getBlue(util::Paint::LOWERRIGHT),currentPaint->getAlpha(util::Paint::LOWERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x + width-1), static_cast<GLfloat>(y + height - 1), depth);

			glColor4f(currentPaint->getRed(util::Paint::LOWERRIGHT),currentPaint->getGreen(util::Paint::LOWERRIGHT),currentPaint->getBlue(util::Paint::LOWERRIGHT),currentPaint->getAlpha(util::Paint::LOWERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x + width -1), static_cast<GLfloat>(y + height -1), depth);	// Bottom Right
			glColor4f(currentPaint->getRed(util::Paint::LOWERLEFT),currentPaint->getGreen(util::Paint::LOWERLEFT),currentPaint->getBlue(util::Paint::LOWERLEFT),currentPaint->getAlpha(util::Paint::LOWERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y + height - 1), depth);

			glColor4f(currentPaint->getRed(util::Paint::LOWERLEFT),currentPaint->getGreen(util::Paint::LOWERLEFT),currentPaint->getBlue(util::Paint::LOWERLEFT),currentPaint->getAlpha(util::Paint::LOWERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y + height -1), depth);	// Bottom Left
			glColor4f(currentPaint->getRed(util::Paint::UPPERLEFT),currentPaint->getGreen(util::Paint::UPPERLEFT),currentPaint->getBlue(util::Paint::UPPERLEFT),currentPaint->getAlpha(util::Paint::UPPERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), depth);
		glEnd();
	}

	void Graphics::drawImage(int textureId, int x, int y, int width, int height)
	{
		applyCurrentColor();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), depth);		// Top Left
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(static_cast<GLfloat>(x + width), static_cast<GLfloat>(y), depth);		// Top Right
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(static_cast<GLfloat>(x + width),static_cast<GLfloat>(y + height), depth);	// Bottom Right
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y + height), depth);	// Bottom Left
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}


	void Graphics::fillRect(int x, int y, int width, int height)
	{
		glBegin(GL_QUADS);
			glColor4f(currentPaint->getRed(util::Paint::UPPERLEFT),currentPaint->getGreen(util::Paint::UPPERLEFT),currentPaint->getBlue(util::Paint::UPPERLEFT),currentPaint->getAlpha(util::Paint::UPPERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), depth);	// Top Left
			glColor4f(currentPaint->getRed(util::Paint::UPPERRIGHT),currentPaint->getGreen(util::Paint::UPPERRIGHT),currentPaint->getBlue(util::Paint::UPPERRIGHT),currentPaint->getAlpha(util::Paint::UPPERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x + width), static_cast<GLfloat>(y), depth);	// Top Right
			glColor4f(currentPaint->getRed(util::Paint::LOWERRIGHT),currentPaint->getGreen(util::Paint::LOWERRIGHT),currentPaint->getBlue(util::Paint::LOWERRIGHT),currentPaint->getAlpha(util::Paint::LOWERRIGHT) * transparency);
			glVertex3f(static_cast<GLfloat>(x + width), static_cast<GLfloat>(y + height), depth);	// Bottom Right
			glColor4f(currentPaint->getRed(util::Paint::LOWERLEFT),currentPaint->getGreen(util::Paint::LOWERLEFT),currentPaint->getBlue(util::Paint::LOWERLEFT),currentPaint->getAlpha(util::Paint::LOWERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y + height), depth);	// Bottom Left
		glEnd();
	}

	void Graphics::setFont(Font* f)
	{
		currentFont = static_cast<int>(GlyphContext::getInstance().setFont(f));
	}

	void Graphics::fillCircle(int x, int y, int radius)
	{
		
		glPointSize(static_cast<GLfloat>(radius));
		glBegin(GL_POINTS);
			glColor4f(currentPaint->getRed(util::Paint::UPPERLEFT),currentPaint->getGreen(util::Paint::UPPERLEFT),currentPaint->getBlue(util::Paint::UPPERLEFT),currentPaint->getAlpha(util::Paint::UPPERLEFT) * transparency);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y),depth);
		glEnd();
		
	}

	void Graphics::setLineWidth(int width)
	{
		glLineWidth(static_cast<GLfloat>(width));
	}

	void Graphics::drawString(int x, int y, std::string str)
	{
		applyCurrentColor();
		Font* f = GlyphContext::getInstance().getFont(currentFont);
		pushMatrix();
		glTranslatef(0,0,depth);
		f->drawString(x,y,str);
		popMatrix();
	}

	void Graphics::popDepth(float d)
	{
		depthStack.pop();
		if(depthStack.size() != 0)
		{
			setDepth(depthStack.top());
		}
		else
		{
			setDepth((float) 1/Component::NORMAL);
		}
	}

	bool Graphics::pushTransparency(float f)
	{
		if(getTransparency() > f)
		{
			transparencyStack.push(getTransparency());
			setTransparency(f);
			return true;
		}
		else
		{
			return false;
		}
	}

	void Graphics::popTransparency()
	{
		transparencyStack.pop();
		if(transparencyStack.size() != 0)
		{
			setTransparency(transparencyStack.top());
		}
		else
		{
			setTransparency(1.0f);
		}
	}

	void Graphics::setTransparency(float f)
	{
		transparency = f;
	}

	float Graphics::getTransparency()
	{
		return transparency;
	}

	float Graphics::getCurrentTransparency()
	{
		// returns the alpha value in currentColor,
		// scaled by the global transparency value,
		// resulting in a proper alpha value.
		float alpha = currentPaint->getAlpha(0);
		float val = alpha * transparency;
		return val;
	}

	bool Graphics::pushDepth(float d)
	{
		if(d > getDepth())
		{
			depthStack.push(getDepth());
			setDepth(d);
			return true;
		}
		else
		{
			return false;
		}
	}

	void Graphics::enableScissor(int x, int y, int width, int height)
	{
		//int viewport[4];
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);

		// adjust from OpenGL coordinate system to ours..
		y = viewport[3] - y - height;

		glScissor(x,y,width,height);
		glEnable(GL_SCISSOR_TEST);
	}

	void Graphics::disableScissor()
	{
		glDisable(GL_SCISSOR_TEST);
	}

	void Graphics::enableBlending()
	{
		glEnable(GL_BLEND);
	}

	void Graphics::disableBlending()
	{
		glDisable(GL_BLEND);
	}

	void Graphics::paintUniqueColoredRect(int index, int x, int y, int width, int height)
	{

		float tmp = getDepth();

		int mode = static_cast<int>(1/getDepth());

		if(mode == Component::NORMAL) // 1/8 = 0.125
		{
			float calc = (float) -1/Component::POPUP_MODAL;
			setDepth(calc); // = -1
		}
		else if(mode == Component::NORMAL_MODAL) // 1/4 = 0.25
		{
			float calc = (float) -1/Component::POPUP;
			setDepth(calc); // = -0.5
		}
		else if(mode == Component::POPUP) // 1/2 = 0.5 
		{
			float calc = (float) -1/Component::NORMAL_MODAL;
			setDepth(calc); // = -0.25
		}
		else if(mode == Component::POPUP_MODAL) // 1/1 = 1
		{
			float calc = (float) -1/Component::NORMAL;
			setDepth(calc); // -0.125
		}
		else
		{
			// throw exception?
			float calc = (float) -1/Component::POPUP_MODAL;
			setDepth(calc); // = -1
		}

		srand(index*2);

		GLubyte red = rand() % 255;
		GLubyte green = rand() % 255;
		GLubyte blue = rand() % 255;

		glColor3ub(red,green,blue);

		glBegin(GL_QUADS);
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y), depth);	// Top Left
			glVertex3f(static_cast<GLfloat>(x + width), static_cast<GLfloat>(y), depth);	// Top Right
			glVertex3f(static_cast<GLfloat>(x + width), static_cast<GLfloat>(y + height), depth);	// Bottom Right
			glVertex3f(static_cast<GLfloat>(x), static_cast<GLfloat>(y + height), depth);	// Bottom Left
		glEnd();

		setDepth(tmp);
	}

	void Graphics::rotate(float degrees)
	{
		glRotatef(degrees,0.0f,0.0f,1.0f);
	}
}