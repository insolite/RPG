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
#include "Component.h"
#include "./Graphics.h"
#include "./Font.h"
#include "./SelectionManager.h"
#include "./FocusManager.h"
#include "./GlyphContext.h"
#include "./util/Point.h"
#include "./util/Color.h"
#include "./util/Rectangle.h"
#include "./util/Dimension.h"
#include "./util/Insets.h"
#include "./util/Interpolator.h"
#include "./event/MouseListener.h"
#include "./event/MouseEvent.h"
#include "./event/FocusListener.h"
#include "./event/FocusEvent.h"
#include "./event/KeyListener.h"
#include "./event/KeyEvent.h"
#include "./event/PropertyListener.h"
#include "./event/PropertyEvent.h"
#include "./border/Border.h"
#include "./ThemeManager.h"
#include "./theme/ThemeComponent.h"
#include "./util/DisplayList.h"

namespace ui
{
/**
 * Constructor/Destructor.
 */
	Component::Component() 
		: visible(true),			// default to visible
		  valid(false),				// not valid, so the layout manager is called	
		  borderPainted(false),		// don't paint borders
		  focus(false),				// nothing is focused
		  transparency(1.0f),		// solid
		  enabled(true),
		  // vectors missing here
		  parent(0),				// no parent
		  theme(0),
		  background(0),
		  foreground(0),
		  rec(),					// no size
		  border(0),				// no border
		  insets(),					// no insets
		  font(-1),					// font
		  depth(static_cast<float>(1/Component::NORMAL)), // normal depth
		  // componentList missing
		  preferredSize(-1,-1),		// invalid size cache
		  rotation(0.0f)
	{
		setThemeName("Component");
	//	displayList = util::DisplayList::createIndex();
	//	isDisplayListCompiled = false;
		
	}

	Component::Component(const Component &rhs)
		:	visible(rhs.visible),
			valid(rhs.valid),
			borderPainted(rhs.borderPainted),
			focus(rhs.focus),
			transparency(rhs.transparency),
			enabled(rhs.enabled),
			mouseListeners(rhs.mouseListeners),
			focusListeners(rhs.focusListeners),
			keyListeners(rhs.keyListeners),
			propertyListeners(rhs.propertyListeners),
			interpolators(rhs.interpolators),
			parent(rhs.parent),
			background(rhs.background),
			foreground(rhs.foreground),
			rec(rhs.rec),
			border(rhs.border),
			insets(rhs.insets),
			font(rhs.font),
			depth(rhs.depth),
			componentList(rhs.componentList),
			preferredSize(rhs.preferredSize),
			rotation(rhs.rotation)
	{
	}

	Component& Component::operator =(const Component& rhs)
	{
		// exception safe..
		Component temp(rhs);
		swap(temp);
		return *this;
	}

	void Component::swap(Component& rhs) throw()
	{
		// swaps the content of one Component with another.
		std::swap(visible,rhs.visible);
		std::swap(valid,rhs.valid);
		std::swap(borderPainted,rhs.borderPainted);
		std::swap(focus,rhs.focus);
		std::swap(transparency,rhs.transparency);
		std::swap(enabled,rhs.enabled);
		std::swap(mouseListeners,rhs.mouseListeners);
		std::swap(focusListeners,rhs.focusListeners);
		std::swap(keyListeners,rhs.keyListeners);
		std::swap(propertyListeners,rhs.propertyListeners);
		std::swap(interpolators,rhs.interpolators);
		std::swap(parent,rhs.parent);
		std::swap(background,rhs.background);
		std::swap(foreground,rhs.foreground);
		std::swap(rec,rhs.rec);
		std::swap(border,rhs.border);
		std::swap(insets,insets);
		std::swap(font,rhs.font);
		std::swap(depth,rhs.depth);
		std::swap(componentList,rhs.componentList);
		std::swap(preferredSize,rhs.preferredSize);
		std::swap(rotation,rhs.rotation);
	}

	Component::~Component()
	{
		removeFocusListeners();
		removeInterpolators();
		removeInterpolators();
		removeKeyListeners();
		removeMouseListeners();
		removePropertyListeners();

	//	util::DisplayList::deleteIndex(displayList);
	}

/**
 * Visibility.
 */

	bool Component::isVisible() const
	{
		return visible;
	}

	void Component::setVisible(bool visibleBool)
	{
		visible = visibleBool;
		event::PropertyEvent e(this,event::PropertyEvent::CORE,event::PropertyEvent::VISIBLE);
		processPropertyEvent(e);
		invalidate();
	}

/**
 * Validation
 */

	bool Component::isValid() const
	{
		return valid;
	}

	void Component::invalidate()
	{
		valid = false;

		//isDisplayListCompiled = false;
		//util::DisplayList::deleteIndex(displayList);
		//displayList = util::DisplayList::createIndex();

		// reset the preferred size, so it's
		// recalculated.
		preferredSize.width = -1;
		preferredSize.height = -1;

		// invalidate all the Components up the hierarchy.
		if(parent != 0 && parent->isValid())
		{
			parent->invalidate();	
		}
	}

	void Component::validate() const
	{
		valid = true;
	}

	void Component::setParent(Component* parent)
	{
		// we should not assign as our own parent :S 
		if(this == parent)
			return;
		/// @TODO should this remove ourselves from a previous parent?
		this->parent = parent;
	}

	Component* Component::getParent() const
	{
		return parent;
	}

/**
 * State
 */
	void Component::setEnabled(bool enable)
	{
		enabled = enable;
		event::PropertyEvent e(this,event::PropertyEvent::CORE,event::PropertyEvent::ENABLED);
		processPropertyEvent(e);
	}

	bool Component::isEnabled() const
	{
		return enabled;
	}

/**
 * Painting.
 */

	void Component::paint(Graphics& g) const
	{
		g.pushMatrix();

		g.translate(getBounds().x,getBounds().y);

		if(rotation != 0.0f)
		{
			int x = getBounds().width /2;
			int y = getBounds().height/2;
		
			g.translate(x,y);
			g.rotate(rotation);
			g.translate(-x,-y);
		}

		// we only paint if its state is visible.
		if(isVisible() && rec.width > 0 && rec.height > 0)
		{
			bool storeDepth = false;

			if(isContainer())
			{
				// we need to store the current depth value,
				// so that it affects all children of this Component.
				storeDepth = g.pushDepth(depth);
			}

			// if this Component is currently not valid, validate it.
			if(!isValid())
			{
				validate();
			}

			if(SelectionManager::getInstance().getRenderMode() == SelectionManager::NORMAL)
			{
				// we're in the normal render mode, so check for transparency,
				// and paint everything
				bool storeTransparency = false;

				storeTransparency = g.pushTransparency(transparency);

				//displayList = g.
				//if(!isDisplayListCompiled)
				//{
				//	util::DisplayList compile(displayList);

					// first paint the background
					paintComponent(g);

					// then any custom painting,
					// which can be done by overloading
					// paintComponent.

					// then paint the borders
					paintBorder(g);

				//	isDisplayListCompiled = true;
				//}
				//else
				//{
				//	util::DisplayList::call(displayList);
				//}

				// then paint the children
				paintChildren(g);

				if(storeTransparency)
				{
					// restore transparency
					g.popTransparency();
				}
			}
			else
			{
				// this is the Picking render mode, we only do special painting
				// here, which helps to speed up this step.

				if(hasMouseListener())
				{
					paintSelectionComponent(g);
				}
				paintChildren(g);
			}

			if(isContainer())
			{
				if(storeDepth)
				{
					// restore depth values
					g.popDepth(depth);
				}
			}
		}
		g.popMatrix();
		//g.translate(-getBounds().x,-getBounds().y);
	}

	void Component::paintComponent(Graphics& g) const
	{
		if(theme != 0)
		{
			theme->paint(g,this);
		}
	}

	void Component::paintChildren(Graphics& g) const
	{
		// do nothing
	}

	void Component::paintBorder(Graphics& g) const
	{
		if(hasBorder() && isBorderPainted())
		{
			border->paintBorder(this,g,0,0,getBounds().width,getBounds().height);
		}
	}

	void Component::paintSelectionComponent(Graphics &g) const
	{
		// if a component has a mouse listener, we need to paint
		// the component to the selection buffer for the picking
		// to work. To do this, we paint the component again, but
		// now in a single, unique color.
		// See also the article online on how the selection mechanism works.
		if(theme != 0)
		{
			theme->paintSelection(g,this);
		}
	}

	void Component::setForeground(util::Paint* c)
	{
		if(foreground == c)
		{
			return;
		}

		foreground = c;
		// should this invalidate the component?
		// colors are automatically repainted, so
		// does changing the color warrant a recalculation
		// of the container?
		invalidate();
	}

	util::Paint* Component::getForeground() const
	{
		// The foreground color has not been set for
		// this component. If you're planning to use
		// the foreground color, make sure you call
		// setForeground(myColor);
		assert(foreground);

		return foreground;
	}

	void Component::setBackground(util::Paint* c)
	{
		if(background == c)
		{
			return;
		}

		background = c;
		
		// should this invalidate the component?
		// colors are automatically repainted, so
		// does changing the color warrant a recalculation
		// of the container?
		invalidate();
	}

	util::Paint* Component::getBackground() const
	{
		// The background color has not been set for
		// this component. If you're planning to use
		// the background color, make sure you call
		// setBackground(myColor);
		assert(background);

		return background;
	}

	const theme::ThemeComponent* Component::getTheme() const
	{
		return theme;
	}

	void Component::setThemeName(const std::string &n)
	{
		name = n;
		setTheme(ThemeManager::getInstance().getTheme()->getThemeComponent(name));
	}

	const std::string & Component::getThemeName() const
	{
		return name;
	}

	void Component::setTheme(theme::ThemeComponent *t)
	{
		if(theme != 0)
		{
			theme->deinstallTheme(this);
		}
		theme = t;
		theme->installTheme(this);
		invalidate();
	}

	void Component::resetTheme()
	{
		if(theme != 0)
		{
			theme->deinstallTheme(this);
			theme->installTheme(this);
			invalidate();
		}
	}

/**
 * Location and size.
 */
	void Component::setLocation(int x, int y)
	{
		rec.x = x;
		rec.y = y;

	//	invalidate();
	}

	void Component::setLocation(const util::Point& p)
	{
		setLocation(p.x,p.y);
	}

	const util::Point Component::getLocation() const
	{
		return util::Point(rec.x,rec.y);
	}

	const util::Point Component::getLocationOnScreen() const
	{
		// start with this location, and add
		// the Points (coordinates of the location) of all parent components
		// to get the location on the screen.
		util::Point location(getLocation());

		for(Component* parent = getParent(); parent != 0;)
		{
			location += parent->getLocation();

			parent = parent->getParent();
		}
		return location;
	}

	void Component::setBounds(const util::Rectangle& rhs)
	{
		setBounds(rhs.x,rhs.y,rhs.width,rhs.height);
	}

	void Component::setBounds(int x, int y, int width, int height)
	{
		rec.width = (width >= 0) ? width : 0;
		rec.height = (height >= 0) ? height : 0;
		rec.x = x;
		rec.y = y;

		invalidate();
	}

	const util::Rectangle& Component::getBounds() const
	{
		return rec;
	}

	const util::Dimension& Component::getPreferredSize() const
	{
		if(preferredSize.width != -1 && preferredSize.height != -1 && isValid())
		{
			return preferredSize;
		}

		// although this method is marked as being const,
		// it still modifies the object state. However these
		// modifications are for caching purposes only, and as
		// such it is allowed via declaring preferredSize mutable.
		preferredSize.width = rec.width;
		preferredSize.height = rec.height;

		if(theme != 0)
		{
			if(theme->getPreferredSize(this).height != -1 && theme->getPreferredSize(this).width != -1)
			{
				preferredSize.width = theme->getPreferredSize(this).width;
				preferredSize.height = theme->getPreferredSize(this).height;
			}
		}

		return preferredSize;
	}

	void Component::setPreferredSize(const util::Dimension& d)
	{
		preferredSize = d;

		validate();
	}

	void Component::setSize(const util::Dimension& rhs)
	{
		setSize(rhs.width,rhs.height);
	}

	void Component::setSize(int width, int height)
	{
		rec.width = (width >= 0) ? width : 0;
		rec.height = (height >= 0) ? height : 0;

		invalidate();
	}

	void Component::setDepth(int type)
	{
		depth = 1.0f/static_cast<float>(type);
	}

	int Component::getDepth() const
	{
		if(depth == 0.0f)
		{
			// throw exception
		}
		return static_cast<int>(1.0f/depth);
	}

/**
 * Container related.
 */

	const ComponentList& Component::getChildren() const
	{
		return componentList;
	}

	bool Component::isContainer() const
	{
		return false;
	}

	bool Component::isRootContainer() const
	{
		return false;
	}

/**
 * Borders and Insets.
 */
	void Component::setBorderPainted(bool enable)
	{
		borderPainted = enable;

		invalidate();
	}

	bool Component::isBorderPainted() const
	{
		return borderPainted;
	}

	bool Component::hasBorder() const
	{
		if(border != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Component::setBorder(border::Border* b)
	{
		// delete current border, and assign new border.
		border = b;

		if(border != 0)
		{
			setInsets(border->getBorderInsets());
		}

		invalidate();
	}

	border::Border * Component::getBorder() const
	{
		// If you see this assert, you're trying to use 
		// a border without there actually being one.
		assert(border);

		return border;
	}

	void Component::setInsets(const util::Insets& i)
	{
		insets = i;

		invalidate();
	}

	const util::Insets& Component::getInsets() const
	{
		return insets;
	}

/**
 * Font
 */
	void Component::setFont(Font* f)
	{
		// we only store a font index here to prevent the GUI
		// from using hundreds of the same fonts.
		font = GlyphContext::getInstance().setFont(f);
		invalidate();
	}

	Font* Component::getFont() const
	{
		return GlyphContext::getInstance().getFont(font);;
	}

/**
 * MouseListeners
 */

	void Component::removeMouseListener(event::MouseListener* l)
	{
		assert(l);
		
		mouseListeners.erase(std::remove(mouseListeners.begin(),mouseListeners.end(),l),mouseListeners.end());
		/*
		event::MouseListenerList::iterator pos = std::find(mouseListeners.begin(),mouseListeners.end(),l);

		if(pos != mouseListeners.end())
		{
			mouseListeners.erase(pos);
		}
		*/
	}

	void Component::removeMouseListeners()
	{
		mouseListeners.clear();
	}

	void Component::addMouseListener(event::MouseListener* l)
	{
		assert(l);
		mouseListeners.push_back(l);
		SelectionManager::getInstance().addComponent(this);
	}

	bool Component::hasMouseListener() const
	{
		if(mouseListeners.size() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Component::processMouseEvent(const event::MouseEvent& e)
	{
		if(!isEnabled())
		{
			return;
		}

		event::MouseListenerList::iterator iterator;
								
		for(iterator = mouseListeners.begin(); iterator != mouseListeners.end(); ++iterator)
		{
			switch(e.getID())
			{
				case event::MouseEvent::MOUSE_PRESSED:
				{
					(*iterator)->mousePressed(e);
					break;
				}
				case event::MouseEvent::MOUSE_RELEASED:
				{
					(*iterator)->mouseReleased(e);
					break;
				}
				case event::MouseEvent::MOUSE_ENTERED:
				{
					(*iterator)->mouseEntered(e);
					break;
				}
				case event::MouseEvent::MOUSE_EXITED:
				{
					(*iterator)->mouseExited(e);
					break;
				}
				case event::MouseEvent::MOUSE_CLICKED:
				{
					(*iterator)->mouseClicked(e);
					break;
				}
				case event::MouseEvent::MOUSE_DRAGGED:
				{
					(*iterator)->mouseDragged(e);
					break;
				}
				case event::MouseEvent::MOUSE_MOTION:
				{
					(*iterator)->mouseMotion(e);
					break;
				}
			}
		}
	}

/**
 * Focus Listener code.
 */
	const event::FocusListenerList Component::getFocusListeners() const
	{
		return focusListeners;
	}

	void Component::removeFocusListeners()
	{
		focusListeners.clear();
	}

	void Component::addFocusListener(event::FocusListener* l)
	{
		focusListeners.push_back(l);
	}

	void Component::removeFocusListener(event::FocusListener* l)
	{
		assert(l);

		focusListeners.erase(std::remove(focusListeners.begin(),focusListeners.end(),l),focusListeners.end());
		/*
		event::FocusListenerList::iterator pos = std::find(focusListeners.begin(),focusListeners.end(),l);

		if(pos != focusListeners.end())
		{
			focusListeners.erase(pos);
		}
		*/
	}
	
	bool Component::hasFocus() const
	{
		return focus;
	}
	
	void Component::setFocus(bool enable)
	{
		focus = enable;
	}

	bool Component::hasFocusListener() const
	{
		return (focusListeners.size() > 0);
	}

	void Component::processFocusEvent(const event::FocusEvent& e)
	{
		event::FocusListenerList::iterator iterator;
								
		for(iterator = focusListeners.begin(); iterator != focusListeners.end(); ++iterator)
		{
			switch(e.getID())
			{
				case event::FocusEvent::FOCUS_LOST:
				{
					if(hasFocus())
					{
						(*iterator)->focusLost(e);
					}
					break;
				}
				case event::FocusEvent::FOCUS_GAINED:
				{
					if(!hasFocus())
					{
						(*iterator)->focusGained(e);
					}
					break;
				}
			}
		}

		if(e.getID() == event::FocusEvent::FOCUS_GAINED)
		{
			if(!hasFocus())
			{
				setFocus(true);
			}
		}
		else
		{
			if(hasFocus())
			{
				setFocus(false);
			}
		}
	}

	bool Component::canHoldPermanentFocus() const
	{
		return true;
	}

/**
 * KeyListener code.
 */
	const event::KeyListenerList Component::getKeyListeners() const
	{
		return keyListeners;
	}

	void Component::removeKeyListeners()
	{
		keyListeners.clear();
	}

	void Component::addKeyListener(event::KeyListener* l)
	{
		assert(l);
		keyListeners.push_back(l);
	}

	void Component::removeKeyListener(event::KeyListener* l)
	{
		assert(l);

		keyListeners.erase(std::remove(keyListeners.begin(),keyListeners.end(),l),keyListeners.end());
		/*
		event::KeyListenerList::iterator pos = std::find(keyListeners.begin(),keyListeners.end(),l);

		if(pos != keyListeners.end())
		{
			keyListeners.erase(pos);
		}
		*/
	}

	bool Component::hasKeyListener() const
	{
		if(keyListeners.size() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Component::processKeyEvent(const event::KeyEvent& e)
	{
		if(!isEnabled())
		{
			return;
		}

		event::KeyListenerList::iterator iter;

		for(iter = keyListeners.begin(); iter != keyListeners.end(); ++iter)
		{
			switch(e.getID())
			{
				case event::KeyEvent::KEY_PRESSED:
				{
					(*iter)->keyPressed(e);
					break;
				}
				case event::KeyEvent::KEY_RELEASED:
				{
					(*iter)->keyReleased(e);
					break;
				}
				case event::KeyEvent::KEY_TYPED:
				{
					(*iter)->keyTyped(e);
					break;
				}
			}
		}
		
		if(e.getID() == event::KeyEvent::KEY_PRESSED)
		{
			// if tab was pressed
			if(e.getKeyCode() == event::KeyEvent::VKUI_TAB && e.getModifier() == event::KeyEvent::MOD_NONE)
			{
				FocusManager::getInstance().focusRightComponent();
			}
			else if(e.getKeyCode() == event::KeyEvent::VKUI_TAB && (e.getModifier() == event::KeyEvent::MOD_LSHIFT || e.getModifier() == event::KeyEvent::MOD_RSHIFT))
			{
				FocusManager::getInstance().focusLeftComponent();
			}
			/*
			else if(e.getKeyCode() == event::KeyEvent::VKUI_RIGHT)
			{
				FocusManager::getInstance().focusRightComponent();
			}
			else if(e.getKeyCode() == event::KeyEvent::VKUI_LEFT)
			{
				FocusManager::getInstance().focusLeftComponent();
			}
			*/
		}
		
	}
/**
 * PropertyListeners
 */
	const event::PropertyListenerList Component::getPropertyListeners() const
	{
		return propertyListeners;
	}

	void Component::removePropertyListeners()
	{
		propertyListeners.clear();
	}

	void Component::addPropertyListener(event::PropertyListener* l)
	{
		assert(l);
		propertyListeners.push_back(l);
	}

	void Component::removePropertyListener(event::PropertyListener* l)
	{
		assert(l);

		propertyListeners.erase(std::remove(propertyListeners.begin(),propertyListeners.end(),l),propertyListeners.end());

		/*
		event::PropertyListenerList::iterator pos = std::find(propertyListeners.begin(),propertyListeners.end(),l);

		if(pos != propertyListeners.end())
		{
			propertyListeners.erase(pos);
		}
		*/
	}

	bool Component::hasPropertyListener() const
	{
		if(propertyListeners.size() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Component::processPropertyEvent(const event::PropertyEvent& e)
	{
		event::PropertyListenerList::iterator iter;

		for(iter = propertyListeners.begin(); iter != propertyListeners.end(); ++iter)
		{
			(*iter)->propertyChanged(e);
		}
	}


	
/**
 * Interpolators.
 */

	void Component::updateComponent(float deltaTime)
	{
		// update interpolaters
		util::InterpolatorList::iterator iter;

		for(iter = interpolators.begin(); iter != interpolators.end(); ++iter)
		{
			(*iter)->update(deltaTime);
		}
	}
	
	void Component::addInterpolator(util::Interpolator* i)
	{
		assert(i);
		interpolators.push_back(i);
	}
	
	void Component::removeInterpolator(util::Interpolator* i)
	{	
		assert(i);

		interpolators.erase(std::remove(interpolators.begin(),interpolators.end(),i),interpolators.end());
/*
		util::InterpolatorList::iterator pos = std::find(interpolators.begin(),interpolators.end(),i);

		if(pos != interpolators.end())
		{
			interpolators.erase(pos);
		}
		*/
	}
	
	void Component::removeInterpolators()
	{
		interpolators.clear();
	}

/** 
 * Transparency.
 */

	void Component::setTransparency(float f)
	{
		if(f > 1.0f)
		{
			f = 1.0f;
		}
		else if(f < 0.0f)
		{
			f = 0.0f;
		}
		transparency = f;
	}

	float Component::getTransparency() const
	{
		return transparency;
	}

	void Component::setRotation(float r)
	{
		if(r > 360.0f)
		{
			r = 360.0f;
		}
		else if(r < 0.0f)
		{
			r = 0.0f;
		}
		rotation = r;
	}

	float Component::getRotation() const
	{
		return rotation;
	}
}