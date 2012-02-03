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

#ifndef FRAME_H
#define FRAME_H

#include "./Window.h"

namespace ui
{
	class MenuBar;

	/**
	 * Frame.
	 * In all GUI's there can only be one Frame,
	 * which is the root container for all other objects.
	 * Frame also provides methods for events, painting
	 * and other stuff (see the individual members).
	 */
	class Frame	:	public Window
	{
	public:
		/**
		 * Frame basic constructor.
		 * Sets up a frame with the given dimensions.
		 * @param
		 *	x	X location of the frame.
		 * @param
		 *	y	Y location of the frame.
		 * @param
		 *	width	Width of the frame.
		 * @param
		 *	height Height of the frame.
		 */
		Frame(int x, int y, int width, int height);

		virtual void paint(Graphics &g);

		/**
		 * Frames destructor.
		 */
		virtual ~Frame();

		/**
		 * Set the MenuBar for this frame.
		 * The menubar will be placed on the 
		 * top of this frame.
		 */
		void setMenuBar(MenuBar *menuBar);

		/**
		 * Returns the MenuBar associated with
		 * this Frame.
		 */
		MenuBar * getMenuBar() const;
	private:
		MenuBar *menubar;

	};
}

#endif
