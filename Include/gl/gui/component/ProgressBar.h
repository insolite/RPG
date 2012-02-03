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
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "../Component.h"

namespace ui
{
	/*
	 * A ProgressBar can display horizontal or verticel
	 * progress bars, which can be used for displaying
	 * 'load' time, or some other event where the user
	 * has to wait, but needs visual feedback of the progress.
	 */
	class ProgressBar :		public Component
	{
	public:
		/**
		 * Create a new ProgressBar with a minimum and
		 * maximum value.
		 * @param
		 *	min Minimum value to use.
		 * @param
		 *	max Maximum value to use.
		 */
		ProgressBar(int min, int max);

		/**
		 * Create a new ProgressBar with a minimum and
		 * maximum value. Also enables you to set the
		 * orientation.
		 * @param
		 *	min Minimum value to use.
		 * @param
		 *	max Maximum value to use.
		 * @param
		 *	orientation Orientation to use for this ProgressBar.
		 */
		ProgressBar(int min, int max, int orientation);


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
		 * Set the percentage indicator to true
		 * or false. If true, the percentage is
		 * also painted as a string, false it only displays
		 * a graphical feedback.
		 */
		void setStringPainted(bool b);

		/**
		 * Returns true if the percentage indicator is painted.
		 * False otherwise.
		 */
		bool isStringPainted() const;

		/**
		 * Sets the maximum value in
		 * this range.
		 */
		void setMaximum(int max);

		/**
		 * Returns the maximum value
		 * in this range.
	  	 */
		int getMaximum() const;

		/**
		 * Sets the minimum value in this
		 * range.
		 */
		void setMinimum(int min);

		/**
		 * Returns the minimum value in
		 * this range.
		 */
		int getMinimum() const;

		/**
		 * Sets the current value for this Range.
		 * Note that the value is bounds checked
		 * with the range minimum and maximum 
		 * values.
	  	 */
		void setValue(int val);

		/**
		 * Returns the current value for this
		 * Range.
		 */
		int getValue() const;

		void setOrientation(int orientation);

		int getOrientation() const;

	private:
		void init(int min, int max, int orientation);
		int min, max, orient, value;
		bool stringPainted;
	};
}

#endif