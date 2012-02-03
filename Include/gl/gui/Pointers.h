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

#ifndef POINTERS_H
#define POINTERS_H

#include <list>
#include <vector>
//#include <string>
#include <stack>
#include <sstream>
#include <algorithm>
// the only C header :O
#include <cassert>

#ifndef NDEBUG
//	#include "../mmgr.h"
#endif

/**
 * Default namespace for all user interface
 * related classes.
 */
namespace ui
{
	/**
	 * Forward declarations. Saves recompile time.
	 */
	class Graphics;
	class Component;
	class Container;
	class Font;
	class GlyphContext;
	class ColorTheme;
	class ColorFactory;
	class Icon;

	namespace theme
	{
		class ThemeComponent;
	}

	class Window;

	namespace border
	{
		class Border;
		class BevelBorder;
	}

	namespace event
	{
		class EventListener;
		class MouseListener;
		class KeyListener;
		class FocusListener;
		class ItemListener;
		class WindowListener;
		class PropertyListener;
		class ChangeListener;

		class Event;
		class MouseEvent;
		class KeyEvent;
		class FocusEvent;
		class ItemEvent;
		class WindowEvent;
		class PropertyEvent;
		class ChangeEvent;

		typedef std::vector<MouseListener*> MouseListenerList;

		typedef std::vector<KeyListener*> KeyListenerList;

		typedef std::vector<FocusListener*> FocusListenerList;

		typedef std::vector<ItemListener*> ItemListenerList;

		typedef std::vector<WindowListener*> WindowListenerList;

		typedef std::vector<PropertyListener*> PropertyListenerList;

		typedef std::vector<ChangeListener*> ChangeListenerList;
	}

	/**
	 * Utility classes.
	 * This namespace contains all the 
	 * utility classes needed for the Gui.
	 */
	namespace util
	{
		class Color;
		class Rectangle;
		class Dimension;
		class Point;
		class Insets;

		class Observer;
		class Observable;
		
		class Interpolator;

		typedef std::vector<Observer*> ObserverList;
		typedef std::vector<Interpolator*> InterpolatorList;
	}

	namespace layout
	{
		class LayoutManager;
		class GridLayout;
		class FlowLayout;
		class PopupLayout;
	}

	typedef std::vector<Component*> ComponentList;

	typedef std::vector<Font*> FontList;

	typedef std::stack<float> FloatStack;
	typedef std::vector<Window*> WindowList;
}

#endif