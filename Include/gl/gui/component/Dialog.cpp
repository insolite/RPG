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
#include "./Dialog.h"
#include "../event/PropertyEvent.h"
#include "../event/WindowEvent.h"

namespace ui
{
	Dialog::Dialog(Window *owner, Icon *icon, const std::string &title)
		:	titleBar(icon,title)
	{
		init(owner);
	}

	Dialog::Dialog(Window *owner, const std::string &title)
		:	titleBar(0,title)
	{
		init(owner);
	}

	void Dialog::init(Window *o)
	{

		// these should trigger the property events,
		// that cause the Theme to adjust it appearance.
		setOwner(o);
		setTitleBar(&titleBar);
		titleBar.addPropertyListener(this);
	//	titleBar.getCloseButton()->addMouseListener(this);
	//	addMouseListener(this);
		listener.setParent(this);
		setThemeName("Dialog");
	}

	const Icon * Dialog::getIcon() const
	{
		return titleBar.getIcon();
	}

	void Dialog::setIcon(Icon *i)
	{
		titleBar.setIcon(i);
		event::PropertyEvent event(this,event::PropertyEvent::SPECIAL,Dialog::ICONCHANGE);
		processPropertyEvent(event);
	}

	const std::string & Dialog::getTitle() const
	{
		return titleBar.getTitle();
	}

	void Dialog::setTitle(const std::string &t)
	{
		titleBar.setTitle(t);
		event::PropertyEvent event(this,event::PropertyEvent::SPECIAL,Dialog::TITLECHANGE);
		processPropertyEvent(event);
	}

	const Window * Dialog::getOwner() const
	{
		return owner;
	}

	void Dialog::setOwner(Window *o)
	{
		o->addOwnedWindow(this);
		owner = o;
		event::PropertyEvent event(this,event::PropertyEvent::SPECIAL,Dialog::OWNERCHANGE);
		processPropertyEvent(event);
	}

	void Dialog::propertyChanged(const event::PropertyEvent &e)
	{
		if(e.getClassID() == event::PropertyEvent::SPECIAL && e.getID() == Dialog::ACTIVECHANGE)
		{
			owner->setActiveWindow(this);
		}
		else if(e.getClassID() == event::PropertyEvent::SPECIAL && e.getID() == Dialog::CLOSE_RELEASED)
		{
			hide();
		}
	}

	void Dialog::DialogListener::setParent(Dialog *d)
	{
		if(parent != 0)
		{
			parent->removeMouseListener(this);
		}
		parent = d;
		d->addMouseListener(this);
	}

	Dialog * Dialog::DialogListener::getParent() const
	{
		return parent;
	}

	Dialog::DialogListener::DialogListener()
		:	parent(0),
			resizing(false)
	{
	}

	Dialog::DialogListener::~DialogListener()
	{
		if(parent != 0)
		{
			parent->removeMouseListener(this);
		}
	}

	void Dialog::DialogListener::mousePressed(const event::MouseEvent &e)
	{
		int x = e.getX();
		int y = e.getY();

		util::Rectangle rec(parent->getBounds().x,parent->getBounds().y,parent->getBounds().width,parent->getBounds().height);
		if(rec.contains(x,y))
		{
			util::Rectangle insets(parent->getBounds().x + parent->getInsets().left, parent->getBounds().y + parent->getInsets().top,parent->getBounds().width - parent->getInsets().left - parent->getInsets().right, parent->getBounds().height - parent->getInsets().top - parent->getInsets().bottom);
			if(!insets.contains(x,y))
			{
				resizing = true;
			}
		}
	}

	void Dialog::DialogListener::mouseReleased(const event::MouseEvent &e)
	{
		resizing = false;
	}

	void Dialog::DialogListener::mouseDragged(const event::MouseEvent &e)
	{
		if(resizing)
		{
			parent->setSize(parent->getBounds().width + e.getX(),parent->getBounds().height + e.getY());
		}
	}
}