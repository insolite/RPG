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
#include "./MenuBar.h"
#include "../FocusManager.h"
#include "../event/PropertyEvent.h"


namespace ui
{
	MenuBar::MenuBar(void)
		:	selected(false),
			selectedMenu(0),
			layout(Component::LEFT,0,0)
	{
		setThemeName("MenuBar");
		setLayout(&layout);
	}

	void MenuBar::add(Menu* menu)
	{
		menu->addMouseListener(this);
		menu->addFocusListener(this);
		menu->addObserver(this);
		addImpl(menu,-1);
	}

	void MenuBar::remove(Menu *menu)
	{
		menu->removeMouseListener(this);
		menu->removeFocusListener(this);
		menu->removeObserver(this);
		removeImpl(menu);
	}

	bool MenuBar::isSelected()
	{
		return selected;
	}

	void MenuBar::selectMenu(Menu *menu)
	{
		event::PropertyEvent selectedEvent(menu,event::PropertyEvent::SPECIAL,Menu::SELECTED);
		menu->processPropertyEvent(selectedEvent);
		menu->setPopupMenuVisible(true);
	}

	void MenuBar::deselectMenu(Menu *menu)
	{
		//if(menu->isSelected())
		//{
			event::PropertyEvent deselectedEvent(menu,event::PropertyEvent::SPECIAL,Menu::DESELECTED);
			menu->processPropertyEvent(deselectedEvent);
			menu->setPopupMenuVisible(false);
		//}
	}

	void MenuBar::mouseEntered(const event::MouseEvent &e)
	{
		if(isSelected())
		{
			if(e.getSource() != selectedMenu)
			{
				// find the new selectedMenu
				ComponentList::const_iterator iter;
				ComponentList list = getChildren();
				for(iter = list.begin(); iter != list.end(); ++iter)
				{
					Menu* menu = static_cast<Menu*>((*iter));

					if(e.getSource() == menu)
					{
						selectMenu(menu);
						selectedMenu = menu;
						selected = true;
						FocusManager::getInstance().setPermanentFocusOwner(selectedMenu);
					}
					else
					{
						deselectMenu(menu);
					}
				}
			}
		}
	}

	void MenuBar::mousePressed(const event::MouseEvent &e)
	{
		ComponentList::const_iterator iter;
		ComponentList list = getChildren();
		for(iter = list.begin(); iter != list.end(); ++iter)
		{
			Menu* menu = static_cast<Menu*>((*iter));

			if(e.getSource() == menu)
			{
				if(menu != selectedMenu)
				{
					selectMenu(menu);
					selectedMenu = menu;
					selected = true;
				}
				else
				{
					deselectMenu(menu);
					selectedMenu = 0;
					selected = false;
				}
			}
			else
			{
				deselectMenu(menu);
			}
		}
	}

	void MenuBar::focusGained(const event::FocusEvent &e)
	{
		if(selectedMenu != e.getSource())
		{
			if(selectedMenu != 0)
			{
				deselectMenu(selectedMenu);
			}
	
			selectedMenu = static_cast<Menu *>(e.getSource());
			selectMenu(selectedMenu);
			selected = true;
		}
	}

	void MenuBar::update(util::Observable *subject)
	{
		selectedMenu = 0;
		selected = false;

		ComponentList::iterator iter;
		ComponentList list = getChildren();
		for(iter = list.begin(); iter != list.end(); ++iter)
		{			
			Menu* menu = static_cast<Menu*>((*iter));

			deselectMenu(menu);
		}
	}

	void MenuBar::focusLost(const event::FocusEvent &e)
	{
		bool found = false;

		ComponentList::iterator iter;
		ComponentList list = getChildren();
		for(iter = list.begin(); iter != list.end(); ++iter)
		{
		
			Menu* menu = static_cast<Menu*>((*iter));

			ComponentList::const_iterator f = std::find(menu->getPopupMenu().getChildren().begin(),menu->getPopupMenu().getChildren().end(),e.getOppositeComponent());
			if(f != menu->getPopupMenu().getChildren().end())
			{
				found = true;
			}
			else
			{
				deselectMenu(menu);
			}
		}

		if(!found)
		{
			selectedMenu = 0;
			selected = false;	
		}
	}
}