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
#include "./Slider.h"
#include "../event/ChangeEvent.h"
#include "../event/ChangeListener.h"

namespace ui
{
	Slider::Slider(float min, float max, float value, int orientation)
	{
		init(min,max,value,orientation);
	}

	Slider::Slider(float min,float max, float value)
	{
		init(min,max,value,Component::HORIZONTAL);
	}

	Slider::Slider(float min, float max)
	{
		init(min,max,0,Component::HORIZONTAL);
	}

	Slider::Slider(int orientation)
	{
		init(0,100,0,orientation);
	}

	void Slider::init(float min, float max, float value, int orientation)
	{
		setMinimum(min);
		setMaximum(max);
		setValue(value);
		setOrientation(orientation);
		adjusting = false;
		knob.addObserver(this);
		//addImpl(&knob,-1);
		setThemeName("Slider");
	}

	float Slider::getMaximum() const
	{
		return max;
	}
	
	void Slider::setMaximum(float m)
	{
		max = m;
	}

	float Slider::getMinimum() const
	{
		return min;
	}
	
	void Slider::setMinimum(float m)
	{
		min = m;
	}

	void Slider::setOrientation(int o)
	{
		orient = o;
	}

	int Slider::getOrientation() const
	{
		return orient;
	}

	void Slider::setValue(float v)
	{
		if(v < getMinimum())
		{
			value = getMinimum();
		}
		else if(v > getMaximum())
		{
			value = getMaximum();
		}
		else
		{
			value = v;
		}

		event::ChangeListenerList::iterator iter;

		for(iter = changeListenerList.begin(); iter != changeListenerList.end(); ++iter)
		{
			(*iter)->stateChanged(event::ChangeEvent(this,event::ChangeEvent::RANGE));
		}
	}

	float Slider::getValue() const
	{
		return value;
	}

	void Slider::setAdjusting(bool a)
	{
		adjusting = a;
	}

	bool Slider::isAdjusting() const
	{
		return adjusting;
	}

	void Slider::addChangeListener(event::ChangeListener *l)
	{
		changeListenerList.push_back(l);
	}

	void Slider::removeChangeListener(event::ChangeListener *l)
	{
		event::ChangeListenerList::iterator pos = std::find(changeListenerList.begin(),changeListenerList.end(),l);

		if(pos != changeListenerList.end())
		{
			changeListenerList.erase(pos);
		}
	}

	void Slider::update(util::Observable* subject)
	{
		adjusting = knob.isDragging();
	}
}