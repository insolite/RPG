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

#ifndef MENU_H
#define MENU_H

#include "./MenuItem.h"
#include "./PopupMenu.h"
#include "../event/MouseListener.h"
#include "../event/FocusListener.h"
#include "../layout/PopupLayout.h"
#include "../util/Observable.h"

namespace ui
{
	/**
	 * A menu which holds other MenuItems.
	 * Menus are added to the MenuBar, and display
	 * PopupMenu's with their children.
	 * @note Note that MenuItems added to this Menu,
	 * are infact added to a PopupMenu, which is a child
	 * of this Menu. This process is invisible to the user.
	 */
	class Menu : public MenuItem, public event::MouseAdapter, public util::Observable, public event::FocusListener
	{
	public:
		/**
		 * Create a new menu with the given text.
		 * @param
		 * str String to use as label for this Menu.
		 */
		Menu(const std::string &label);

		Menu(Icon *icon, const std::string &label);

		/**
		 * Add a MenuItem to this menu.
		 * @param
		 * menuItem MenuItem to add to this Menu.
		 */
		void add(MenuItem* menuItem);

		/**
		 * Removes a menuitem from this menu.
		 * 
		 */
		void remove(MenuItem *menuItem);

		/**
		 * Set the visible state of the PopupMenu
		 * containing the MenuItems.
		 * This can be used to programatically set the
		 * visibility state of the PopupMenu.
		 */
		void setPopupMenuVisible(bool visible);

		enum PROPERTYCHANGES
		{
			SELECTED = 10,
			DESELECTED = 11
		};

		/**
		 * Returns the PopupMenu used by this Menu.
		 */
		const PopupMenu& getPopupMenu() const;

		/**
		 * Returns the visibility state of the PopupMenu
		 * and thus the MenuItems contained by this Menu.
		 */
		bool isPopupMenuVisible() const;

		virtual bool canHoldPermanentFocus() const;

		virtual ~Menu();
	private:
		void mouseClicked(const event::MouseEvent &e);

		void mouseEntered(const event::MouseEvent &e);
		void mouseExited(const event::MouseEvent &e);

		void mouseMotion(const event::MouseEvent &e);

		void focusLost(const event::FocusEvent &e);
		void focusGained(const event::FocusEvent &e);

		void init();
		PopupMenu popupMenu;
		layout::PopupLayout layout;
	};
}
#endif