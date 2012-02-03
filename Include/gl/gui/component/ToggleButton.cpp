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
#include "./ToggleButton.h"
#include "../event/MouseEvent.h"

namespace ui
{
	ToggleButton::ToggleButton(Icon *icon)
	{
		init(icon,"",false);
	}

	ToggleButton::ToggleButton(Icon *icon, bool selected)
	{
		init(icon,"",selected);
	}

	ToggleButton::ToggleButton(const std::string &text)
	{
		init(0,text,false);
	}
	
	ToggleButton::ToggleButton(const std::string &text, bool selected)
	{
		init(0,text,selected);
	}

	void ToggleButton::init(Icon *icon,const std::string &text, bool selected)
	{
		setDefaultIcon(icon);
		setText(text);
		setSelected(selected);
		setThemeName("ToggleButton");
		addFocusListener(this);
		addMouseListener(this);
	}

	void ToggleButton::focusGained(const event::FocusEvent &e)
	{
		setFocusPainted(true);
	}

	void ToggleButton::focusLost(const event::FocusEvent &e)
	{
		setFocusPainted(false);
	}

	void ToggleButton::mousePressed(const event::MouseEvent &e)
	{
		if(e.getButton() == event::MouseEvent::MOUSE_BUTTON2)
		{
			if(!isSelected())
			{
				setSelected(true);
				event::ItemEvent selected(this,event::ItemEvent::SELECTED);
				processItemEvent(selected);
			}
			else
			{
				setSelected(false);
				event::ItemEvent deselected(this,event::ItemEvent::DESELECTED);
				processItemEvent(deselected);
			}
		}
	}

	void ToggleButton::addItemListener(event::ItemListener *l)
	{
		assert(l);

		itemListenerList.push_back(l);
	}

	void ToggleButton::removeItemListener(event::ItemListener *l)
	{
		assert(l);

		event::ItemListenerList::iterator iter = std::find(itemListenerList.begin(),itemListenerList.end(),l);

		if(iter != itemListenerList.end())
		{
			itemListenerList.erase(iter);
		}
	}

	void ToggleButton::processItemEvent(const event::ItemEvent &e)
	{
		event::ItemListenerList::iterator iter;
		for(iter = itemListenerList.begin(); iter != itemListenerList.end(); ++iter)
		{
			(*iter)->itemStateChanged(e);
		}
	}
}