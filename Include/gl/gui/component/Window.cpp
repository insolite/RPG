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
#include "./Window.h"
#include "../event/WindowEvent.h"
#include "../Graphics.h"

namespace ui
{
	Window::Window()
		:	rootPane(0),
			activeWindow(0),
			titleBar(0)
	{
		setVisible(false);
		setLayout(&layout);
		setThemeName("Window");
	}

	Window::~Window()
	{
		removeWindowListeners();
		removeOwnedWindows();
	}

	void Window::addOwnedWindow(Window *window)
	{
		window->setParent(this);
		windowList.push_back(window);

	}

	const WindowList& Window::getOwnedWindows() const
	{
		return windowList;
	}

	void Window::removeOwnedWindow(Window *window)
	{
		WindowList::iterator pos = std::find(windowList.begin(),windowList.end(),window);

		if(pos != windowList.end())
		{
			(*pos)->setParent(0);
			windowList.erase(pos);
		}
	}

	void Window::removeOwnedWindows()
	{
		windowList.clear();
	}

	void Window::add(Component *comp, int constraints)
	{
		// You must set a rootpane before using add.
		assert(rootPane);
		if(rootPane != 0)
		{
			rootPane->add(comp,constraints);
		}
	}

	void Window::remove(Component *comp)
	{
		assert(rootPane);
		if(rootPane != 0)
		{
			rootPane->remove(comp);
		}
	}

	void Window::addWindowListener(event::WindowListener *listener)
	{
		windowListenerList.push_back(listener);
	}

	void Window::removeWindowListener(event::WindowListener *listener)
	{
		event::WindowListenerList::iterator pos = std::find(windowListenerList.begin(),windowListenerList.end(),listener);

		if(pos != windowListenerList.end())
		{
			delete (*pos);
			windowListenerList.erase(pos);
		}
	}

	void Window::removeWindowListeners()
	{
		windowListenerList.clear();
	}

	const event::WindowListenerList Window::getWindowListeners() const
	{
		return windowListenerList;
	}

	void Window::setTitleBar(TitleBar *tit)
	{
		assert(tit);
		if(tit != 0)
		{
			addImpl(tit,layout::BorderLayout::NORTH);
			titleBar = tit; // :O
		}
	}

	TitleBar * Window::getTitleBar() const
	{
		return titleBar;
	}

	Container* Window::getContentPane() const
	{
		return rootPane;
	}

	void Window::setContentPane(Container *pane)
	{
		if(rootPane != 0)
		{
			rootPane->removeAll();
			remove(rootPane);
			delete rootPane;
		}

		rootPane = pane;
		addImpl(rootPane,layout::BorderLayout::CENTER);
	}

	void Window::hide()
	{
		setVisible(false);
		
		event::WindowEvent event(this,event::WindowEvent::CLOSED);
		processWindowEvent(event);

		invalidate();
	}

	void Window::show()
	{
		setVisible(true);

		event::WindowEvent event(this,event::WindowEvent::OPENED);
		processWindowEvent(event);

		invalidate();
	}

	void Window::pack()
	{
		setSize(getPreferredSize());
		validate();
	}

	void Window::setActiveWindow(Window *window)
	{
		if(activeWindow != 0)
		{
			event::WindowEvent deactivated(activeWindow,event::WindowEvent::DEACTIVATED);
			activeWindow->processWindowEvent(deactivated);
		}

		activeWindow = window;

	

		if(activeWindow != 0)
		{
			event::WindowEvent activated(activeWindow,event::WindowEvent::ACTIVATED);
			activeWindow->processWindowEvent(activated);

			// swap the Components in the list to adjust the rendering order.
			// This way active windows are always on top of the other windows.
			WindowList::iterator pos = std::find(windowList.begin(),windowList.end(),activeWindow);

			if(pos != windowList.end())
			{
				Window* tmp = (*pos);
				windowList.erase(pos);
				windowList.push_back(tmp);
			}
		}
	}

	Window * Window::getActiveWindow() const
	{
		return activeWindow;
	}

	bool Window::isRootContainer() const
	{
		return true;
	}

	void Window::updateComponent(float deltaTime)
	{
		Container::updateComponent(deltaTime);

		WindowList::const_iterator iter;
		for(iter = windowList.begin(); iter != windowList.end(); ++iter)
		{
			(*iter)->updateComponent(deltaTime);
		}
	}

	void Window::paintChildren(Graphics &g) const
	{
		Container::paintChildren(g);

		WindowList::const_iterator iter;
		for(iter = windowList.begin(); iter != windowList.end(); ++iter)
		{
			(*iter)->paint(g);
		}
	}

	void Window::processWindowEvent(const event::WindowEvent &e)
	{
		event::WindowListenerList::const_iterator iterator;
								
		for(iterator = windowListenerList.begin(); iterator != windowListenerList.end(); ++iterator)
		{
			int type = e.getID();

			switch(type)
			{
				case event::WindowEvent::ACTIVATED:
				{
					(*iterator)->windowActivated(e);
					break;
				}
				case event::WindowEvent::DEACTIVATED:
				{
					(*iterator)->windowDeactivated(e);
					break;
				}
				case event::WindowEvent::CLOSED:
				{
					(*iterator)->windowClosed(e);
					break;
				}
				case event::WindowEvent::OPENED:
				{
					(*iterator)->windowOpened(e);
					break;
				}
			}
		}
	}
}