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
#include "./Scroller.h"
#include "../event/ChangeEvent.h"
#include "../event/ChangeListener.h"

namespace ui
{
//	namespace
//	{
		Scroller::Scroller(float min, float max, float value, int orientation)
		{
			init(min,max,value,orientation);
		}

		Scroller::Scroller(float min,float max, float value)
		{
			init(min,max,value,Scroller::HORIZONTAL);
		}

		Scroller::Scroller(float min, float max)
		{
			init(min,max,0,Scroller::HORIZONTAL);
		}

		Scroller::Scroller(int orientation)
		{
			init(0,100,0,orientation);
		}

		void Scroller::init(float min, float max, float value, int orientation)
		{
			setMinimum(min);
			setMaximum(max);
			setValue(value);
			setOrientation(orientation);
			adjusting = false;
			setThumbSize(33);
			setThemeName("Scroller");
		}

		float Scroller::getMaximum() const
		{
			return max;
		}
		
		void Scroller::setMaximum(float m)
		{
			max = m;
		}

		float Scroller::getMinimum() const
		{
			return min;
		}
		
		void Scroller::setMinimum(float m)
		{
			min = m;
		}

		void Scroller::setOrientation(int o)
		{
			orient = o;
		}

		int Scroller::getOrientation() const
		{
			return orient;
		}

		void Scroller::setValue(float v)
		{
			if(v != value)
			{
				if(v <= getMinimum())
				{
					value = getMinimum();
				}
				else if(v >= getMaximum())
				{
					value = getMaximum();
				}
				else
				{
					value = v;
				}

				if(getParent())
				{
					event::ChangeListenerList::iterator iter;

					for(iter = changeListenerList.begin(); iter != changeListenerList.end(); ++iter)
					{
						(*iter)->stateChanged(event::ChangeEvent(getParent(),event::ChangeEvent::RANGE));
					}
				}
				else
				{
					event::ChangeListenerList::iterator iter;

					for(iter = changeListenerList.begin(); iter != changeListenerList.end(); ++iter)
					{
						(*iter)->stateChanged(event::ChangeEvent(this,event::ChangeEvent::RANGE));
					}
				}
			}
		}

		void Scroller::addChangeListener(event::ChangeListener *l)
		{
			changeListenerList.push_back(l);
		}

		void Scroller::removeChangeListener(event::ChangeListener *l)
		{
			event::ChangeListenerList::iterator pos = std::find(changeListenerList.begin(),changeListenerList.end(),l);

			if(pos != changeListenerList.end())
			{
				changeListenerList.erase(pos);
			}
		}

		float Scroller::getValue() const
		{
			return value;
		}

		void Scroller::setAdjusting(bool a)
		{
			adjusting = a;
		}

		bool Scroller::isAdjusting() const
		{
			return adjusting;
		}

		void Scroller::setThumbSize(int percentage)
		{
			thumbSize = percentage;
		}

		int Scroller::getThumbSize() const
		{
			return thumbSize;
		}
//	}
}