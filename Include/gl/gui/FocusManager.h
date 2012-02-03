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

#ifndef FOCUSMANAGER_H
#define FOCUSMANAGER_H

#include "./Pointers.h"

namespace ui
{
	/**
	 * Singleton class which manages
	 * the Component(s) that are currently
	 * focused.
	 */
	class FocusManager
	{
	public:

		FocusManager();

		static FocusManager & getInstance()
		{
			static FocusManager obj;
			return obj;
		}

		/**
		 * Set the given Component as permanent focus owner.
		 * Permanent means that this component keeps focus, until
		 * setPermanentFocusOwner is called again, even if setFocusOwner
		 * is called.
		 * @param
		 *	c Component to set permanent focus to.
		 * @note
		 *	When called, this unsets the previous permanent focus owner
		 *	and sends the appropriate events.
		 */
		void setPermanentFocusOwner(Component* c);

		/**
		 * Returns the current permanent focus owner.
		 */
		Component* getPermanentFocusOwner();

		/**
		 * Set the given Component as focus owner.
		 * The focus owner is usually a child of the permanent
		 * focus owner (such as a MenuItem is a child of Menu),
		 * and focus is returned to the permanent focus owner,
		 * once the focus owner looses its focus.
		 * @param
		 *	c Component to set focus to.
		 * @see
		 *	setPermanentFocusOwner
		 */
		void setFocusOwner(Component* c);

		/**
		 * Returns the current focus owner.
		 */
		Component* getFocusOwner();

		/**
		 * Sends keypresses to the currently focused
		 * Component.
		 */
		void keyPressed(int keyCode, int modifier);

		/**
		 * Sends keyreleases to the currently focused
		 * Component.
		 */
		void keyReleased(int keyCode, int modifier);

		/**
		 * Move focus to the right, ie; when
		 * someone pressed tab. If there is no
		 * current focus owner, nothing happens.
		 */
		void focusRightComponent();

		/**
		 * Focus the component left (in the component tree hierarchy)
		 * of the currently focused Component. If there is no
		 * currently focused Component, nothing happens.
		 */
		void focusLeftComponent();

	private:
		void buildStack(Component *node, bool backward);
		std::deque<Component *> stack;
		Component* focusOwner, *permanentFocusOwner, *oppositeComponent;
	};
}
#endif