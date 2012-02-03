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

#ifndef WINDOW_H
#define WINDOW_H

#include "../CompoundComponent.h"
#include "../event/WindowListener.h"
#include "../layout/BorderLayout.h"
#include "./TitleBar.h"

namespace ui
{
	/**
	 * Defines basic functionality for Window based Components.
	 */
	class Window : public CompoundComponent
	{
	public:
		/**
		 * Creates a Window with default values.
		 */
		Window();

		/**
		 * Frees memory used by this class.
		 */
		virtual ~Window();

		/**
		 * Add a window to this Window. This makes
		 * this Window the parent of the added window.
		 * @param
		 *	window the Window to add as a child.
		 */
		void addOwnedWindow(Window *window);

		/**
		 * Removes a registered window from this window.
		 * @param
		 *	window the window to be deleted.
		 */
		void removeOwnedWindow(Window *window);

		/**
		 * Removes all registered windows from this
		 * window.
		 */
		void removeOwnedWindows();

		/**
		 * Returns the owned Windows.
		 */
		const WindowList& getOwnedWindows() const;

		/**
		 * Sets the content pane for this Frame.
		 * @param
		 *	container container that should be used as content pane.
		 */
		void setContentPane(Container *pane);

		/**
		 * Returns the current content Pane.
		 * A content pane is a Container which is the parent
		 * of all Components that are added to Window.
		 * @return
		 *	the active content pane.
		 */
		Container * getContentPane() const;

		/**
		 * Add a Component to the Window.
		 * @note Components are added to the contentpane,
		 *  not to the Window directly. As such these are only
		 *  convenience methods, not methods that act directly
		 *  on this container. A more true way would be to use
		 *  getContentPane().add().
		 */
		void add(Component* comp, int constraints = -1);

		/**
		 * Removes a Component from this Window.
		 * @note Note that the Components are removed
		 * from the contentpane, not the Window itself.
		 */
		void remove(Component *comp);

		/**
		 * Shows the Window.
		 * Initially, all windows are invisible. Issuing show()
		 * on them, makes them display.
		 * @note
		 *	The difference with setVisible(true) is that this function
		 *	also sends a window opened event to registered window listeners.
		 */
		void show();

		/**
		 * Hides the Window.
		 * Hides the window if it's current visible. Otherwise
		 * this command is ignored.
		 * @note
		 *	The difference with setVisible(false) is that this function
		 *	also sends a window closed event to registered window listeners.
		 */
		void hide();


		/**
		 * Issues a recalculation of preferred sizes.
		 * Pack recalculates all the dimensions of the Components
		 * inside the window, and tries to give each their preferred size.
		 */
		void pack();

		/**
		 * Updates the Window with the frame time.
		 * This function is used internally to update
		 * the components framerate independent. It's best
		 * not to call this method directly.
		 * @param
		 *	deltaTime time between frame updates.
		 */
		void updateComponent(float deltaTime);

		/**
		 * Returns wether this Container is a top level Container.
		 */
		virtual bool isRootContainer() const;

		/**
		 * Adds a window listener to this Window.
		 * @param
		 *	listener The listener to be added to the Window.
		 */
		void addWindowListener(event::WindowListener *listener);

		/**
		 * Removes a window listener from this Window.
		 * @param
		 *	listener The listener to be removed from the Window.
		 */
		void removeWindowListener(event::WindowListener *listener);

		/**
		 * Removes all window listeners from this Window.
		 */
		void removeWindowListeners();

		/**
		 * Returns all registered Window listeners.
		 * @return
		 *	All registered Window Listeners.
		 */
		const event::WindowListenerList getWindowListeners() const;

		/**
		 * Forwards the event to the registered listeners and appropriate
		 * methods.
		 * @param
		 *	e Event to be forwarded.
		 */
		void processWindowEvent(const event::WindowEvent &e);

		void setTitleBar(TitleBar *titleBar);

		TitleBar * getTitleBar() const;

		void setActiveWindow(Window *window);

		Window * getActiveWindow() const;

	protected:
		/**
		 * Paints the Window and it's children.
		 * @param
		 *	g The graphics instance.
		 */
		void paintChildren(Graphics& g) const;
		
		

	private:
		void paintOwnedWindows(Graphics& g) const;

		Container* rootPane;
		event::WindowListenerList windowListenerList;

		WindowList windowList;
		Window* activeWindow;
		layout::BorderLayout layout;
		TitleBar *titleBar;
	};
}
#endif