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
#ifndef GUI_H
#define GUI_H

#include "./Graphics.h"
#include "./component/Frame.h"
#include "./GlyphContext.h"

namespace ui
{
	/**
	 * The Gui class manages everything related to the Gui.
	 * It has several methods which need to be called in order
	 * for the Gui to fully work. There should only be one Gui
	 * in your whole program. This does not mean you cannot have
	 * more than one user interface, just only one Gui instance.
	 * To create more than one interface, use multiple Frame instances
	 * and register them with your Gui instance.
	 */
	class Gui
	{
	public:
		Gui();

		/**
		 * Add a frame instance to the Gui manager. 
		 * @param
		 *	frame Frame to be added to the Gui.
		 * @note
		 *	Note that frames are rendered in the order they
		 *	are added. 
		 */
		void addFrame(Frame* frame);

		/**
		 * Removes a frame instance from the Gui manager.
		 * This means the frame will no longer be painted
		 * or updated. If you just disable a Frame temporarely,
		 * the setVisible(false) or hide() options are a better choice
		 * than removing the frame from the Gui.
		 * @param
		 *	frame Frame to be removed from the Gui.
		 */
		void removeFrame(Frame* frame);

		/**
		 * Draw the Gui.
		 * This should be called every frame,
		 * and if possible when in orthographic mode.
		 */
		void paint();

		/**
		 * Export functions
		 */

		/**
		 * Send mouse coordinates to the Gui.
		 * This should be done everyframe, as
		 * the mouse coordinates are used by the 
		 * picking engine.
		 */
		void importMouseMotion(int x, int y);

		/**
		 * Send a mouse press to the Gui.
		 * @param
		 *	button The button that was pressed. Valid
		 *	values are stored in /event/MouseEvent.h:
		 *	<ul>
		 *		<li>MOUSE_BUTTON1 - Left mouse button</li>
		 *		<li>MOUSE_BUTTON2 - Right mouse button</li>
		 *		<li>MOUSE_BUTTON3 - Third button</li>
		 *		<li>MOUSE_SCROLL_UP - Scroll wheel up</li>
		 *		<li>MOUSE_SCROLL_DOWN - Scroll wheel down</li>
		 *	</ul>
		 *	These values are stored in an enum, so it is advisable
		 *	to use the enumerated constants instead of integers.
		 * @see
		 *	MouseEvent
		 */
		void importMousePressed(int button);

		/**
		 * Send a mouse release to the Gui.
		 * @param
		 *	button The button that was released. Valid
		 *	values are stored in MouseEvent
		 *	<ul>
		 *		<li>MOUSE_BUTTON1 - Left mouse button</li>
		 *		<li>MOUSE_BUTTON2 - Right mouse button</li>
		 *		<li>MOUSE_BUTTON3 - Third button</li>
		 *		<li>MOUSE_SCROLL_UP - Scroll wheel up</li>
		 *		<li>MOUSE_SCROLL_DOWN - Scroll wheel down</li>
		 *	</ul>
		 *	These values are stored in an enum, so it is advisable
		 *	to use the enumerated constants instead of integers.
		 * @see
		 *	MouseEvent
		 */
		void importMouseReleased(int button);

		/**
		 * Send a key press to the Gui.
		 * Possible values for the parameters can
		 * be found in KeyEvent
		 * @see
		 *	KeyEvent
		 */
		void importKeyPressed(int keyCode, int modifier);

		/**
		 * Send a key release to the Gui.
		 * Possible values for the parameters can
		 * be found in KeyEvent
		 * @see
		 *	KeyEvent
		 */
		void importKeyReleased(int keyCode, int modifier);

		/**
		 * Send a time based update to the Gui.
		 * @param
		 *	deltaTime the delta time between the last two frames.
		 * @note
		 *	This is not required, but all time based
		 *	motion in the Gui will not work if you do
		 *	not call this function.
		 */
		void importUpdate(float deltaTime);

		/**
		 * Sets the font factory for the Gui. Font factories
		 * are used to create all Fonts in the system, and have
		 * to be implemented by the end user.
		 * Also see the online article.
		 */
		void setFontFactory(AbstractFontFactory *factory);

		/**
		 * Returns the FontFactory currently in use.
		 */
		AbstractFontFactory * getFontFactory() const;
	private:
		Graphics g;
		int mouseX,mouseY;
		std::vector<Frame*> frameList;
	};
}

#endif
