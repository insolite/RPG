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
#include "./Label.h"

namespace ui
{
	Label::Label(Icon *icon, const std::string &label)
	{
		init(icon,label);
	}

	Label::Label(const std::string &label)
	{
		init(0,label);
	}

	void Label::init(Icon *icon, const std::string &label)
	{
		setThemeName("Label");
		setHorizontalAlignment(Component::LEFT);
		setVerticalAlignment(Component::CENTER);
		setIcon(icon);
		setText(label);
	}

	void Label::setMargin(const util::Insets &m)
	{
		margin = m;
	}

	const util::Insets & Label::getMargin() const
	{
		return margin;
	}

	void Label::setText(const std::string &label)
	{
		text = label;
	}

	const std::string & Label::getText() const
	{
		return text;
	}

	void Label::setHorizontalAlignment(int alignment)
	{
		horizontalAlignment = alignment;
	}
	
	void Label::setVerticalAlignment(int alignment)
	{
		verticalAlignment = alignment;
	}

	int Label::getHorizontalAlignment() const
	{
		if(horizontalAlignment < 0)
		{
			horizontalAlignment = Component::CENTER;
		}
		return horizontalAlignment;
	}
	
	int Label::getVerticalAlignment() const
	{
		if(verticalAlignment < 0)
		{
			verticalAlignment = Component::CENTER;
		}
		return verticalAlignment;
	}

	void Label::setIcon(Icon *i)
	{
		icon = i;
	}

	Icon * Label::getIcon() const
	{
		return icon;
	}

}