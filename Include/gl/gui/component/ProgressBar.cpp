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
#include "./ProgressBar.h"


namespace ui
{
	ProgressBar::ProgressBar(int min, int max, int orientation)
	{
		init(min,max,orientation);
	}

	ProgressBar::ProgressBar(int min, int max)
	{
		init(min,max,ProgressBar::HORIZONTAL);
	}

	bool ProgressBar::isStringPainted() const
	{
		return stringPainted;
	}

	void ProgressBar::setStringPainted(bool b)
	{
		stringPainted = b;
	}

	void ProgressBar::init(int min, int max, int orientation)
	{
		setThemeName("ProgressBar");
		setMinimum(min);
		setMaximum(max);
		setValue(0);
		setOrientation(orientation);
		setStringPainted(true);
	}

	void ProgressBar::setMaximum(int m)
	{
		max = m;
	}

	int ProgressBar::getMaximum() const
	{
		return max;
	}

	void ProgressBar::setMinimum(int m)
	{
		min = m;
	}

	int ProgressBar::getMinimum() const
	{
		return min;
	}

	void ProgressBar::setValue(int v)
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
	}

	int ProgressBar::getValue() const
	{
		return value;
	}

	void ProgressBar::setOrientation(int orientation)
	{
		orient = orientation;
	}

	int ProgressBar::getOrientation() const
	{
		return orient;
	}

}