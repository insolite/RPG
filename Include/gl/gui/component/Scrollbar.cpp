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
#include "./Scrollbar.h"
#include "../event/ChangeEvent.h"
#include "../event/ChangeListener.h"
#include "../event/MouseEvent.h"

namespace ui
{
	Scrollbar::Scrollbar(float min, float max, float value, int orientation)
		:	incrementButton(0,""),
			decrementButton(0,""),
			scroller(min,max,value,orientation),
			changeBy(0.0f)
	{
		init();
	}

	Scrollbar::Scrollbar(float min,float max, float value)
		:	incrementButton(0,""),
			decrementButton(0,""),
			scroller(min,max,value,Scroller::HORIZONTAL),
			changeBy(0.0f)
	{
		init();
	}

	Scrollbar::Scrollbar(float min, float max)
		:	incrementButton(0,""),
			decrementButton(0,""),
			scroller(min,max,0,Scroller::HORIZONTAL),
			changeBy(0.0f)
	{
		init();
	}

	Scrollbar::Scrollbar(int orientation)
		:	incrementButton(0,""),
			decrementButton(0,""),
			scroller(0,100,0,orientation),
			changeBy(0.0f)
	{
		init();
	}

	void Scrollbar::init()
	{
		setLayout(&layout);

		if(getOrientation() == Scroller::HORIZONTAL)
		{
			addImpl(&incrementButton,layout::BorderLayout::EAST);
			addImpl(&decrementButton,layout::BorderLayout::WEST);
		}
		else
		{
			addImpl(&incrementButton,layout::BorderLayout::SOUTH);
			addImpl(&decrementButton,layout::BorderLayout::NORTH);
		}
		addImpl(&scroller,layout::BorderLayout::CENTER);
		

		incrementButton.addMouseListener(this);
		decrementButton.addMouseListener(this);

		setThemeName("Scrollbar");
	}

	Button * Scrollbar::getIncrementButton()
	{
		return &incrementButton;
	}

	Button * Scrollbar::getDecrementButton()
	{
		return &decrementButton;
	}

	float Scrollbar::getMaximum() const
	{
		return scroller.getMaximum();
	}
	
	void Scrollbar::setMaximum(float m)
	{
		scroller.setMaximum(m);
	}

	float Scrollbar::getMinimum() const
	{
		return scroller.getMinimum();
	}
	
	void Scrollbar::setMinimum(float m)
	{
		scroller.setMinimum(m);
	}

	void Scrollbar::setOrientation(int o)
	{
		if(o == Scroller::HORIZONTAL && getOrientation() == Scroller::VERTICAL)
		{
			removeImpl(&incrementButton);
			removeImpl(&decrementButton);

			addImpl(&incrementButton,layout::BorderLayout::EAST);
			addImpl(&decrementButton,layout::BorderLayout::WEST);
		}
		else if(o == Scroller::VERTICAL && getOrientation() == Scroller::HORIZONTAL)
		{
			removeImpl(&incrementButton);
			removeImpl(&decrementButton);

			addImpl(&incrementButton,layout::BorderLayout::SOUTH);
			addImpl(&decrementButton,layout::BorderLayout::NORTH);
		}

		scroller.setOrientation(o);
	}

	int Scrollbar::getOrientation() const
	{
		return scroller.getOrientation();
	}

	void Scrollbar::setValue(float v)
	{
		scroller.setValue(v);
	}

	float Scrollbar::getValue() const
	{
		return scroller.getValue();
	}

	void Scrollbar::setAdjusting(bool a)
	{
		scroller.setAdjusting(a);
	}

	bool Scrollbar::isAdjusting() const
	{
		return scroller.isAdjusting();
	}

	void Scrollbar::addChangeListener(event::ChangeListener *l)
	{
		scroller.addChangeListener(l);
	}

	void Scrollbar::removeChangeListener(event::ChangeListener *l)
	{
		scroller.removeChangeListener(l);
	}

	void Scrollbar::updateComponent(float deltaTime)
	{
		setValue(getValue() + changeBy);
	}

	void Scrollbar::mousePressed(const event::MouseEvent &e)
	{
		if(e.getSource() == &incrementButton)
		{
			changeBy = 3.0f;
		}
		else if(e.getSource() == &decrementButton)
		{
			changeBy = -3.0f;
		}
	}

	void Scrollbar::mouseReleased(const event::MouseEvent &e)
	{
		changeBy = 0.0f;
	}

	int Scrollbar::getThumbSize() const
	{
		return scroller.getThumbSize();
	}

	void Scrollbar::setThumbSize(int percentage)
	{
		scroller.setThumbSize(percentage);
	}
}