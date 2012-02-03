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
#include "LineBorder.h"
#include "../Graphics.h"
#include "../util/Color.h"

namespace ui
{
	namespace border
	{		
		LineBorder::LineBorder(const util::Color& c, int thickn)
			:	insets(thickn,thickn,thickn,thickn),
				color(c)
		{
		}

		LineBorder::LineBorder(const util::Color &c, const util::Insets &i)
			:	insets(i),
				color(c)
		{
		}

		LineBorder::LineBorder(const util::Color& c)
			:	insets(1,1,1,1),
				color(c)
		{
		}

		LineBorder::LineBorder()
			:	insets(1,1,1,1),
				color(util::Color(0,0,0))
		{
		}

		LineBorder::LineBorder(const LineBorder& rhs)
			:	Border(static_cast<Border>(rhs)),
				insets(rhs.insets),
				color(rhs.color)
		{
		}

		LineBorder& LineBorder::operator=(const LineBorder& rhs)
		{
			LineBorder temp(rhs);
			swap(temp);
			return *this;
		}

		void LineBorder::swap(LineBorder& rhs) throw()
		{
			std::swap(color,rhs.color);
			std::swap(insets,rhs.insets);
		}

		void LineBorder::paintBorder(const Component* component, Graphics& g, int x, int y, int w, int h) const
		{
			g.setPaint(&color);

			// top
			g.fillRect(x, y, x + w, y + insets.top);

			// right
			g.fillRect(x + w - insets.right, y, x + insets.right, y + h);

			// bottom
			g.fillRect(x, y + h - insets.bottom, x + w, y + insets.bottom);

			// left
			g.fillRect(x,y, x + insets.left, y + h);
		}

		const util::Color& LineBorder::getColor() const
		{
			return color;
		}

		void LineBorder::setColor(const util::Color &c)
		{
			color = c;
		}

		const util::Insets LineBorder::getBorderInsets() const
		{
			return insets;
		}
	}
}
