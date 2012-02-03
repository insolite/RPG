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
#ifndef SLIDER_H
#define SLIDER_H

#include "../CompoundComponent.h"
#include "./Knob.h"
#include "../util/Observer.h"

namespace ui
{
	class Slider : public CompoundComponent, public util::Observer
	{
	public:
		Slider(int orientation);
		Slider(float min, float max);
		Slider(float min, float max, float value);
		Slider(float min, float max, float value, int orientation);

		/**
		 * Component orientation.
		 */
		enum ORIENTATION
		{
			/**
				* Defines a vertically laid out
				* Range Component.
				*/
			VERTICAL,

			/**
				* Defines a horizontally laid out
				* Range Component.
				*/
			HORIZONTAL
		};

		/**
		 * Returns the maximum value
		 * in this range.
		 */
		float getMaximum() const;

		/**
		 * Sets the maximum value in
		 * this range.
		 */
		void setMaximum(float m);

		/**
		 * Returns the minimum value in
		 * this range.
		 */
		float getMinimum() const;

		/**
		 * Sets the minimum value in this
		 * range.
		 */
		void setMinimum(float m);

		/**
		 * Sets the current value for this Range.
		 * Note that the value is bounds checked
		 * with the range minimum and maximum 
		 * values.
		 */
		void setValue(float v);

		/**
		 * Returns the current value for this
		 * Range.
		 */
		float getValue() const;

		/**
		 * Sets the orientation of this
		 * Range. Can either be HORIZONTAL
		 * or VERTICAL.
		 */
		void setOrientation(int o);

		/**
		 * Returns the orientation of this Range.
		 */
		int getOrientation() const;

		bool isAdjusting() const;

		void setAdjusting(bool adjusting);

		void addChangeListener(event::ChangeListener *l);

		void removeChangeListener(event::ChangeListener *l);
	private:
		void update(util::Observable* subject);
		int orient;
		float min, max, value;
		bool adjusting;
		void init(float min, float max, float value, int orientation);
		event::ChangeListenerList changeListenerList;
		Knob knob;
	};
}

#endif