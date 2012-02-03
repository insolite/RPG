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
#include "./Menu.h"
#include "../FocusManager.h"
#include "../event/PropertyEvent.h"
#include "../event/FocusEvent.h"
#include "../event/MouseEvent.h"

namespace ui
{
	Menu::Menu(const std::string &label)
		:	MenuItem(label)
	{
		init();
	}

	Menu::Menu(Icon *icon, const std::string &label)
		:	MenuItem(icon,label)
	{
		init();
	}

	void Menu::init()
	{
		setThemeName("Menu");
		setLayout(&layout);
		addImpl(&popupMenu,-1);
	}

	Menu::~Menu()
	{
	}

	const PopupMenu& Menu::getPopupMenu() const
	{
		return popupMenu;
	}

	void Menu::add(MenuItem* menuItem)
	{
		menuItem->addMouseListener(this);
		menuItem->addFocusListener(this);
		popupMenu.add(menuItem);
	}

	void Menu::remove(MenuItem *menuItem)
	{
		menuItem->removeMouseListener(this);
		menuItem->addFocusListener(this);
		popupMenu.remove(menuItem);
	}

	bool Menu::canHoldPermanentFocus() const
	{
		return true;
	}

	void Menu::setPopupMenuVisible(bool visible)
	{
		popupMenu.setVisible(visible);
	}

	bool Menu::isPopupMenuVisible() const
	{
		return popupMenu.isVisible();
	}

	void Menu::mouseClicked(const event::MouseEvent &e)
	{
		// here we notify the observer that the menu should close.
		// The observer is usually a Menubar, but it could be nothing
		// in the case of a standalone menuitem. In this case, this is a no-op.
		setPopupMenuVisible(false);
		setChanged();
		notifyObserver();

		FocusManager::getInstance().setPermanentFocusOwner(0);
	}

	void Menu::mouseEntered(const event::MouseEvent &e)
	{
		FocusManager::getInstance().setFocusOwner(e.getSource());
	}

	void Menu::mouseExited(const event::MouseEvent &e)
	{
		if(e.getSource()->hasFocus())
		{
			FocusManager::getInstance().setFocusOwner(0);
		}
	}

	void Menu::mouseMotion(const event::MouseEvent &e)
	{
	}

	void Menu::focusLost(const event::FocusEvent &e)
	{
	}

	void Menu::focusGained(const event::FocusEvent &e)
	{
	}
}
