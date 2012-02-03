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
#include "./ScrollPane.h"
#include "../Graphics.h"

namespace ui
{
	ScrollPane::ScrollPane(Component *comp)
		:	horizontalScrollbar(Scrollbar::HORIZONTAL),
			verticalScrollbar(Scrollbar::VERTICAL),
			layout(false),
			view(comp),
			x(0),
			y(0)

	{
		view.setScrollPane(this);
		setLayout(&layout);
		setThemeName("ScrollPane");

		verticalScrollbar.addChangeListener(this);
		horizontalScrollbar.addChangeListener(this);

		horizontalScrollbar.setVisible(false);
		verticalScrollbar.setVisible(false);

		addImpl(&view,layout::BorderLayout::CENTER);
		addImpl(&horizontalScrollbar,layout::BorderLayout::SOUTH);
		addImpl(&verticalScrollbar,layout::BorderLayout::EAST);
	}

	Scrollbar * ScrollPane::getHorizontalScrollbar()
	{
		return &horizontalScrollbar;
	}

	Scrollbar * ScrollPane::getVerticalScrollbar()
	{
		return &verticalScrollbar;
	}

	void ScrollPane::stateChanged(const event::ChangeEvent &e)
	{
		if(e.getSource() == &horizontalScrollbar)
		{
			view.setHorizontalLocation(horizontalScrollbar.getValue());
		}
		else if(e.getSource() == &verticalScrollbar)
		{
			view.setVerticalLocation(verticalScrollbar.getValue());
		}
	}

// ---------------------------------------------------------------------------

	ScrollPane::ViewContainer::ViewContainer(Component *child)
		:	view(child)
	{
		// constructor parameters cannot be 0 (NULL).
		assert(view);
		add(view);
	}

	void ScrollPane::ViewContainer::setScrollPane(ScrollPane *parent)
	{
		scrollPane = parent;
	}

	const util::Dimension & ScrollPane::ViewContainer::getPreferredSize() const
	{
		return view->getPreferredSize();
	}

	void ScrollPane::ViewContainer::setHorizontalLocation(float value)
	{
		float screen = static_cast<float>(view->getBounds().width);
		float window = static_cast<float>(getBounds().width);
	
		float tmp = ((screen-window) / 100.0f) * value;

		int y = view->getLocation().y;

		view->setLocation(static_cast<int>(-tmp),y);
	}

	void ScrollPane::ViewContainer::setVerticalLocation(float value)
	{
		float screen = static_cast<float>(view->getBounds().height);
		float window = static_cast<float>(getBounds().height);
	
		float tmp = ((screen-window) / 100.0f) * value;

		int x = view->getLocation().x;

		view->setLocation(x,static_cast<int>(-tmp));
	}

	void ScrollPane::ViewContainer::paintChildren(Graphics &g) const
	{
		assert(scrollPane);

		// the child always has its preferred size...
		view->setSize(view->getPreferredSize());

		if(view->getBounds().width > getBounds().width)
		{
			scrollPane->getHorizontalScrollbar()->setVisible(true);
		}
		else
		{
			scrollPane->getHorizontalScrollbar()->setVisible(false);
		}

		if(view->getBounds().height > getBounds().height)
		{
			scrollPane->getVerticalScrollbar()->setVisible(true);
		}
		else
		{
			scrollPane->getVerticalScrollbar()->setVisible(false);
		}
	//	scrollPane->getParent()->invalidate();
		int hpercentage = static_cast<int>((static_cast<float>(getBounds().width) / static_cast<float>(view->getBounds().width)) * 100.0f);
		scrollPane->getHorizontalScrollbar()->setThumbSize(hpercentage);

		int vpercentage = static_cast<int>((static_cast<float>(getBounds().height) / static_cast<float>(view->getBounds().height)) * 100.0f);
		scrollPane->getVerticalScrollbar()->setThumbSize(vpercentage);


		util::Point p(getLocationOnScreen());
		g.enableScissor(p.x,p.y,getBounds().width,getBounds().height);
		Container::paintChildren(g);
		g.disableScissor();
	}


}