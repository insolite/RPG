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
#include "./AbstractButton.h"
#include "../util/Insets.h"
#include "../event/PropertyEvent.h"
#include "../event/MouseEvent.h"
#include "../event/FocusEvent.h"

namespace ui
{
	AbstractButton::AbstractButton()
		:	defaultIcon(0),
			selectedIcon(0),
			disabledDefaultIcon(0),
			disabledSelectedIcon(0),
			selected(false)
	{
		setHorizontalAlignment(Component::CENTER);
		setVerticalAlignment(Component::CENTER);
		setFocusPainted(false);
		setContentAreaFilled(true);
		listener.setAbstractButton(this);
	}

	AbstractButton::~AbstractButton()
	{
	}

	void AbstractButton::setHorizontalAlignment(int alignment)
	{
		horizontalAlignment = alignment;
	//	invalidate();
	}
	
	void AbstractButton::setVerticalAlignment(int alignment)
	{
		verticalAlignment = alignment;
	//	invalidate();
	}

	int AbstractButton::getHorizontalAlignment() const
	{
		if(horizontalAlignment < 0)
		{
			horizontalAlignment = Component::CENTER;
		}
		return horizontalAlignment;
	}
	
	int AbstractButton::getVerticalAlignment() const
	{
		if(verticalAlignment < 0)
		{
			verticalAlignment = Component::CENTER;
		}
		return verticalAlignment;
	}

	bool AbstractButton::isFocusPainted() const
	{
		return focusPainted;
	}

	void AbstractButton::setFocusPainted(bool enable)
	{
		focusPainted = enable;
		event::PropertyEvent e(this,event::PropertyEvent::SPECIAL,AbstractButton::FOCUSPAINTCHANGED);
		processPropertyEvent(e);
	//	invalidate();
	}

	void AbstractButton::setContentAreaFilled(bool b)
	{
		contentAreaPainted = b;
	//	invalidate();
	}

	bool AbstractButton::isContentAreaFilled() const
	{
		return contentAreaPainted;
	}

	void AbstractButton::setMargin(const util::Insets &m)
	{
		margin = m;
	//	invalidate();
	}

	const util::Insets & AbstractButton::getMargin() const
	{
		return margin;
	}

	void AbstractButton::setText(const std::string &value)
	{
		str = value;
		event::PropertyEvent e(this,event::PropertyEvent::SPECIAL,AbstractButton::TEXTCHANGE);
		processPropertyEvent(e);
	//	invalidate();
	}

	const std::string & AbstractButton::getText() const
	{
		return str;
	}

	void AbstractButton::setSelected(bool value)
	{
		selected = value;
		if(selected)
		{
			event::PropertyEvent e(this,event::PropertyEvent::SPECIAL,AbstractButton::SELECTED);
			processPropertyEvent(e);
		}
		else
		{
			event::PropertyEvent e(this,event::PropertyEvent::SPECIAL,AbstractButton::DESELECTED);
			processPropertyEvent(e);
		}
	//	invalidate();
	}

	bool AbstractButton::isSelected() const
	{
		return selected;
	}

	void AbstractButton::setDefaultIcon(Icon *icon)
	{
		defaultIcon = icon;
	//	invalidate();
	}

	void AbstractButton::setDisabledDefaultIcon(Icon *icon)
	{
		disabledDefaultIcon = icon;
	}

	void AbstractButton::setSelectedIcon(Icon *icon)
	{
		selectedIcon = icon;
	//	invalidate();
	}

	void AbstractButton::setDisabledSelectedIcon(Icon *icon)
	{
		disabledSelectedIcon = icon;
	//	invalidate();
	}

	Icon * AbstractButton::getDefaultIcon() const
	{
		return defaultIcon;
	}

	Icon * AbstractButton::getDisabledDefaultIcon() const
	{
		return disabledDefaultIcon;
	}

	Icon * AbstractButton::getSelectedIcon() const
	{
		return selectedIcon;
	}

	Icon * AbstractButton::getDisabledSelectedIcon() const
	{
		return disabledSelectedIcon;
	}

	void AbstractButton::doPressed()
	{
		// this is a bit of a hack, but it ensures that code depending
		// on MouseListeners is properly called.
		event::MouseEvent pressedEvent(this,event::MouseEvent::MOUSE_PRESSED,0,0,event::MouseEvent::MOUSE_BUTTON2);
		processMouseEvent(pressedEvent);

		event::FocusEvent focusEvent(this,event::FocusEvent::FOCUS_GAINED,false);
		processFocusEvent(focusEvent);
	}

	void AbstractButton::doReleased()
	{
		event::MouseEvent releasedEvent(this,event::MouseEvent::MOUSE_RELEASED,0,0,event::MouseEvent::MOUSE_BUTTON2);
		processMouseEvent(releasedEvent);
	}

	void AbstractButton::doClicked()
	{
		event::MouseEvent clickedEvent(this,event::MouseEvent::MOUSE_CLICKED,0,0,event::MouseEvent::MOUSE_BUTTON2);
		processMouseEvent(clickedEvent);
	}

	AbstractButton::AbstractButtonListener::AbstractButtonListener()
		:	parent(0)
	{
	}

	AbstractButton::AbstractButtonListener::~AbstractButtonListener()
	{
		if(parent != 0)
		{
			parent->removeKeyListener(this);
		}
	}

	void AbstractButton::AbstractButtonListener::setAbstractButton(AbstractButton *button)
	{
		if(parent != 0)
		{
			parent->removeKeyListener(this);
		}
		parent = button;
		parent->addKeyListener(this);
	}

	AbstractButton * AbstractButton::AbstractButtonListener::getAbstractButton()
	{
		return parent;
	}

	void AbstractButton::AbstractButtonListener::keyPressed(const event::KeyEvent &e)
	{
		if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
		{
			parent->doPressed();
		}
	}

	void AbstractButton::AbstractButtonListener::keyReleased(const event::KeyEvent &e)
	{
		if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
		{
			parent->doReleased();
		}
	}

	void AbstractButton::AbstractButtonListener::keyTyped(const event::KeyEvent &e)
	{
		if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
		{
			parent->doClicked();
		}
	}

}