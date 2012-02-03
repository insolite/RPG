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
#include "./Container.h"
#include "./Graphics.h"
#include "./util/Dimension.h"
#include "./util/Rectangle.h"
#include "./layout/LayoutManager.h"

namespace ui
{
/**
 * Constructor/Destructor.
 */
	Container::Container()
		:	layout(0)
	{
	}

	Container::Container(const Container& rhs)
		: Component(static_cast<Component>(rhs))
	{
		layout = rhs.layout;
	}

	void Container::swap(Container &rhs) throw()
	{
		std::swap(layout,rhs.layout);
	}

	Container& Container::operator =(const Container& rhs)
	{
		Container temp(rhs);
		swap(temp);
		return *this;
	}

	Container::~Container()
	{
		removeAll();
	}

/**
 * Component overloads.
 */

	bool Container::isContainer() const
	{
		return true;
	}

	bool Container::hasChildren() const
	{
		return componentList.size() != 0; 
	}

	void Container::setEnabled(bool enable)
	{
		ComponentList::const_iterator iterator;
		for(iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
		{
			(*iterator)->setEnabled(enable);
		}
		Component::setEnabled(enable);
	}

	const util::Dimension& Container::getPreferredSize() const
	{
		// if the valid flag is set to true, and the cache is valid, return
		// the cached value.
		if(isValid() && preferredSize.width != -1 && preferredSize.height != -1)
		{
			return preferredSize;
		}

		// if we have a layout manager, use it to calculate
		// the preferredSize.
		if(layout != 0)
		{
			preferredSize = layout->preferredLayoutSize(this);
		}
		else
		{
		// otherwise, just stick to the Components preferredSize.
			preferredSize = Component::getPreferredSize();
		}
		return preferredSize;
	}

	void Container::updateComponent(float deltaTime)
	{
		Component::updateComponent(deltaTime);

		ComponentList::const_iterator iterator;
		for(iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
		{
			(*iterator)->updateComponent(deltaTime);
		}
	}

/**
 * Painting.
 */
	void Container::paintChildren(const Container* parent, Graphics& g) const
	{
		// check if this is a Container, if this Container has children
		// and if it's visible. If so, start painting the children.
		if(parent->isContainer() && parent->hasChildren() && parent->isVisible())
		{
			// paint components
			ComponentList::const_iterator iterator;

			// this piece of code is waiting for a new C++ standard :P
			//std::for_each(componentList.begin(),componentList.end(),std::bind2nd(std::mem_fun(&Component::paint),g));
			for(iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
			{
				(*iterator)->paint(g);
			}
		}
	}

	void Container::paintChildren(Graphics& g) const
	{
		paintChildren(this,g);
	}

	void Container::paintComponent(Graphics& g) const
	{
		Component::paintComponent(g);	
	}

/**
 * Container operations.
 */
	void Container::add(Component* comp, int constraints)
	{
		addImpl(comp,constraints);
	}

	void Container::addImpl(Component* component, int constraints)
	{
		// a component cannot be null.
		assert(component);

		// make this Container the added Components parent.
		component->setParent(this);

		// also notify the layout manager (if we have one) of the new Component
		if(layout != 0)
			layout->addLayoutComponent(component, constraints);

		// finally, add the Component.
		componentList.push_back(component);

		// and invalidate the Container.
		if(isValid())
			invalidate();
	}

	int Container::getNumberOfChildren() const
	{
		return static_cast<int>(componentList.size());
	}
/*
	Component* Container::getChild(int n) const
	{
		if(n > getNumberOfChildren())
			return 0;
		else
		{
			ComponentList::const_iterator iterator;

			int i = 0;
			for(iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
			{
				if(i == n)
					return (*iterator);
				i++;
			}
			return 0;
		}
	}
*/
	void Container::remove(Component* component)
	{
		removeImpl(component);
	}

	void Container::removeImpl(Component *component)
	{
		ComponentList::iterator iter = std::find(componentList.begin(), componentList.end(),component);
		if(iter != componentList.end())
		{
			(*iter)->setParent(0);
			if(layout != 0)
			{
				layout->removeLayoutComponent((*iter));
			}
			componentList.erase(iter);
		}
		if(isValid())
		{
			invalidate();
		}
	}

	void Container::removeAll()
	{
		componentList.clear();
	}

/**
 * Container layout
 */
	void Container::setLayout(layout::LayoutManager* newLayout)
	{
		layout = newLayout;
	}

	void Container::validate() const
	{
		validateTree();
		Component::validate();
	}

	void Container::validateTree() const
	{
		// only validate down the tree if our
		// valid flag is set to false.
		if(!isValid())
		{
			// check if we have a layoutmanager and children
			// if so, do a layout call.
			if(layout != 0 && getNumberOfChildren() != 0)
				layout->layoutContainer(this);

			ComponentList::const_iterator iterator;

			// call validate on the Containers children, so the validateTree
			// call propogates down the tree.
			for(iterator = componentList.begin(); iterator != componentList.end(); ++iterator)
			{
				if(!(*iterator)->isValid() && !(*iterator)->isRootContainer())
				{
					(*iterator)->validate();
				}
			}
		}
	}

	bool Container::isRootContainer() const
	{
		return false;
	}
}