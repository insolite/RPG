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

#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "./Config.h"
#include "./Pointers.h"
#include "./util/Color.h"
#include "./util/Paint.h"

namespace ui
{
	/**
	 * Graphics Context.
	 * Graphics is the base class for all drawing related 
	 * code, and thus also contains OpenGL code.
	 */
	class Graphics
	{
	public:
		/**
		 * Creates a Graphics instance.
		 * For normal use you'll only want one of these.
		 */
		Graphics();
		
		/**
		 * Destroys the Graphics instance, and returns
		 * all memory used by it.
		 */
		~Graphics();

		/**
		 * Translate the orientation.
		 */
		void translate(int x, int y);

		/**
		 * Save translation matrix.
		 */
		void pushMatrix();

		/**
		 * Restore translation matrix.
		 */
		void popMatrix();

		/**
		 * Sets the rendering depth.
		 * @param
		 *	newDepth new depth should range from 0 to 1.
		 */
		void setDepth(float newDepth);

		/**
		 * Returns the currently used depth.
		 */
		float getDepth();

		/**
		 * Sets the current color(paint), this will be used by any further call
		 * to the Graphics context, until another setPaint() call is made.
		 */
		void setPaint(const util::Paint* paint);

		/**
		 * Draws a rectangle to the screen at the given location, with
		 * specified width and height.
		 */
		void drawRect(int x, int y, int width, int height);

		/**
		 * Draws a filled rectangle to the screen at the given location, with
		 * specified width and height.
		 */
		void fillRect(int x, int y, int width, int height);

		/**
		 * draws an image
		 */
		void drawImage(int textureId, int x, int y, int width, int height);

		/**
		 * Draws a line from one point to another.
		 */
		void drawLine(int x1, int y1, int x2, int y2);

		/*
		 * Sets the current font.
		 */
		void setFont(Font* f);

		/**
		 * Draws a string in the current font.
		 */
		void drawString(int x, int y, std::string str);

		/**
		 * Fills a circle at the given location with given radius.
		 */
		void fillCircle(int x, int y, int radius);

		/**
		 * Set the linewidth.
		 * @note this is a state switch, you must set
		 * it back to the original value after using it.
		 */
		void setLineWidth(int width);

		/**
		 * Store the current depth.
		 */
		bool pushDepth(float d);

		/**
		 * Restore the previous depth.
		 */
		void popDepth(float d);

		/**
		 * Enable scissor testing, which effectively 'masks' out
		 * a rendering area.
		 * This is automatically calculated from
		 * GUI coordinates ((0,0) in top-left corner) to OpenGL
		 * coordinates ((0,0) in bottom-left corner).
		 * @note Note that this is a state flag, you must return
		 * to normal mode by using disableScissor().
		 * @see disableScissor();
		 * @param
		 *	x horizontal location of the scissor area.
		 * @param
		 *	y vertical location of the scissor area.
		 * @param
		 *	width scissor area width.
		 * @param
		 *	height scissor area height.
		 */
		void enableScissor(int x, int y, int width, int height);

		/**
		 * Disables the scissor area testing.
		 */
		void disableScissor();

		/**
		 * Enables alpha blending.
		 */
		void enableBlending();

		/**
		 * Disables alpha blending.
		 */
		void disableBlending();

		/**
		 * Paint a unique colored rectangle to the screen.
		 * This is used by the SelectionManager, and should
		 * not be used for normal painting.
		 */
		void paintUniqueColoredRect(int index, int x, int y, int width, int height);

		/**
		 * Rotate the coordinate system over the x axis.
		 */
		void rotate(float degrees);

		bool pushTransparency(float f);
		void popTransparency();

		void setTransparency(float f);
		float getTransparency();
	private:
		/**
		 * Apply the current color.
		 */
		void applyCurrentColor();

		float getCurrentTransparency();
		float depth, transparency;
		FloatStack depthStack, transparencyStack;
	//	util::Color currentColor;
		int currentFont;

		const util::Paint *currentPaint;
	};
}
#endif