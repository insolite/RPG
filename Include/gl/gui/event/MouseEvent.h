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

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Event.h"


namespace ui
{
	namespace event
	{	
		/**
		 * Mouse related events.
		 */
		class MouseEvent : public Event
		{
		public:

			enum MouseEventTypes
			{
				/**
				 * Mouse is pressed.
				 */
				MOUSE_PRESSED,
				/**
				 * Mouse is released.
				 */
				MOUSE_RELEASED,

				/**
				 * Mouse is clicked (pressed and released)
				 */
				MOUSE_CLICKED,

				/**
				 * The mouse pointer exited the Component.
				 */
				MOUSE_EXITED,

				/**
				 * The mouse is dragged.
				 */
				MOUSE_DRAGGED,

				/**
				 * The mouse pointer entered the Component.
				 */
				MOUSE_ENTERED,

				/**
				 * The mouse has moved
				 */
				MOUSE_MOTION
			};

			enum MouseButtons
			{
				MOUSE_BUTTON1, //left
				MOUSE_BUTTON2, // right
				MOUSE_BUTTON3, // 3rd button
				MOUSE_SCROLL_UP, // scroll wheel up
				MOUSE_SCROLL_DOWN // scroll wheel down
			};

			/**
			 * Creates a new MouseEvent with the specified
			 * Component as source.
			 */
			MouseEvent(Component* sourceComponent, int id, int x, int y, int mouseButton);

			/**
			 * Returns the button that generated this event.
			 */
			int getButton() const;

			/**
			 * Returns the x location of the MouseEvent.
			 */
			int getX() const;

			/**
			 * Returns the y location of the MouseEvent.
			 */
			int getY() const;
		private:
			int mouseX, mouseY, button;
		};
	}
}
#endif