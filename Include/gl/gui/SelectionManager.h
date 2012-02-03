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

#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include "./Pointers.h"
#include "./Config.h"

namespace ui
{
	/**
	 * SelectionManager handles picking of objects.
	 * How this works, you can read at:
	 * http://www.bramstein.nl in the articles section.
	 * A short description of the mouse handling follows.
	 * MouseMotion:
	 * A mousemotion event is sent each frame to the currently focused (selected)
	 * component. This is done so that
	 * a Component can receive MouseMotion events while the mouse is not
	 * actually located at the Component.
	 * MouseEntered, MouseExited:
	 * The mouse location is checked every frame, and each time the mouse
	 * enters or exits an event is sent, this happens independently from the
	 * other events.
	 * MouseClicked, MousePressed, MouseReleased:
	 * when a mouse is pressed, the current location is probed for a Component,
	 * and if found, events are sent.
	 * @note
	 *	This is a Singleton object.
	 */

	class SelectionManager
	{
	public:
		enum RENDERMODE
		{
			/**
			 * Normal render mode.
			 */
			NORMAL,
			/**
			 * Selection render mode.
			 */
			SELECTION
		};

		/**
		 * Sets the rendermode.
		 * @param
		 *	m Rendermode to use.
		 * @see
		 *	RENDERMODE
		 */
		void setRenderMode(int m);

		/**
		 * Returns the currently used render mode.
		 */
		int getRenderMode() const;

		/**
		 * Register a component with the SelectionManager.
		 * Registering means that the object will be pickable,
		 * and receive mouse input.
		 * @param
		 *	comp Component to add.
		 */
		void addComponent(Component* comp);

		/**
		 * Unregister a component with the SelectionManager.
		 * @param
		 *	comp Component to remove.
		 */
		void removeComponent(Component* comp);

		/**
		 * Returns the identifier for the given Component.
		 * The identifier is unique and can be used (and is)
		 * for calculating the unique color for picking.
		 * @param
		 *	comp The Component for which to return the id.
		 */
		int getComponentId(const Component* comp) const;


		/**
		 * Begins the update.
		 * Should be called at the start of a frame.
		 */
		void beginUpdate(int x, int y);

		/**
		 * Returns the Component located at x,y.
		 * Returns NULL(0) if no Component is present.
		 */
		Component* getComponentAt(int x, int y) const;

		/**
		 * Input feeds.
		 * Inputs mouse motion to the SelectionManager.
		 */
		void mouseMotion(int x, int y);
		
		/**
		 * Input feeds.
		 * A mouse button went down.
		 */
		void mousePressed(int button);
		
		/**
		 * Input feeds.
		 * A mouse button was released (up).
		 */
		void mouseReleased(int button);

		/**
		 * Returns an instance of the SelectionManager.
		 */
		static SelectionManager& getInstance()
		{
			static SelectionManager obj;
			return obj;
		}
	private:
		SelectionManager();
		~SelectionManager();
		SelectionManager(const SelectionManager&);
		SelectionManager& operator=(const SelectionManager&);

		class IntegerColor
		{
		public:
			IntegerColor(int r, int g, int b) : red(r), green(g), blue(b) {};
			int red;
			int green;
			int blue;
		};

		class ColorRegisterValue
		{
		public:
			ColorRegisterValue() : color(0,0,0), textureColor(0,0,0) {};
			int index;
			Component *comp;
			IntegerColor color;
			IntegerColor textureColor;
		};

		std::vector<ColorRegisterValue> colorRegister;

		//std::vector< std::pair<int, Component*> > pickingList;
		//std::vector< std::pair<util::Color, util::Color> > colorRegister;
		int idCounter;
		int mode;
		Component* foundComponent,*tempComponent, *hoverOverComponent;
		bool pressed;
		int buttonPressed;
		int mouseX, mouseY;
		int lastX, lastY;

		static const int textureWidth = 64;
		static const int textureHeight = 64;
		GLubyte texture[textureWidth][textureHeight][3];
		GLuint textureId;
	};
}

#endif