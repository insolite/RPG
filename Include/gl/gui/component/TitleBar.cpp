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
#include "./TitleBar.h"
#include "../event/PropertyEvent.h"
#include "./Dialog.h"

namespace ui
{
	void TitleBar::setTitle(const std::string &title)
	{
		titleLabel.setText(title);
	}

	const std::string & TitleBar::getTitle() const
	{
		return titleLabel.getText();
	}

	void TitleBar::setIcon(Icon *i)
	{
		titleLabel.setIcon(i);
	}

	Icon * TitleBar::getIcon() const
	{
		return titleLabel.getIcon();
	}

	TitleBar::TitleBar(Icon *icon, const std::string &label)
		:	closeButton(0,""),
			titleLabel(icon,label)
	{
		init();
	}

	TitleBar::TitleBar(const std::string &label)
		:	closeButton(0,""),
			titleLabel(0,label)
	{
		init();
	}

	void TitleBar::init()
	{
		setThemeName("TitleBar");
		setLayout(&layout);
		addImpl(&closeButton,layout::BorderLayout::EAST);
		addImpl(&titleLabel,layout::BorderLayout::CENTER);
		dragging = false;
		nextX = 0;
		nextY = 0;
		addMouseListener(this);
		closeButton.addMouseListener(this);
	}

	Label * TitleBar::getTitleLabel()
	{
		return &titleLabel;
	}

	Button * TitleBar::getCloseButton()
	{
		return &closeButton;
	}

	void TitleBar::mousePressed(const event::MouseEvent &e)
	{
		if(e.getSource() == this)
		{
			dragging = true;

			//@todo: we could make this even more loosely coupled by moving activechange to Component (or make it a core event)
			event::PropertyEvent event(this,event::PropertyEvent::SPECIAL,Dialog::ACTIVECHANGE);
			processPropertyEvent(event);
		}
	}

	void TitleBar::mouseReleased(const event::MouseEvent &e)
	{
		if(e.getSource() == this)
		{
			dragging = false;
		}
		else
		{
			event::PropertyEvent event(this,event::PropertyEvent::SPECIAL,Dialog::CLOSE_RELEASED);
			processPropertyEvent(event);
		}
	}

	void TitleBar::mouseDragged(const event::MouseEvent &e)
	{
		if(e.getSource() == this)
		{
			if(dragging)
			{
				nextX = getParent()->getLocationOnScreen().x + e.getX();
				nextY = getParent()->getLocationOnScreen().y + e.getY();				
				getParent()->setLocation(nextX,nextY);
			}
		}
	}

}