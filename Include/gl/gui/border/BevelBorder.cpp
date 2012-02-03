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
#include "./BevelBorder.h"
#include "../Graphics.h"
#include "../util/Color.h"

namespace ui
{
	namespace border
	{
		BevelBorder::BevelBorder(int type)
			:	raisedShadow(130,130,130),
				raisedHighlight(255,255,255),
				loweredShadow(130,130,130),
				loweredHighlight(180,180,180)
		{
			setType(type);
		}

		BevelBorder::BevelBorder()
			:	raisedShadow(130,130,130),
				raisedHighlight(255,255,255),
				loweredShadow(130,130,130),
				loweredHighlight(180,180,180)
		{
			setType(RAISED);
		}

		BevelBorder::BevelBorder(const BevelBorder& rhs)
			:	Border(static_cast<Border>(rhs)),
				isRaised(rhs.isRaised)
		{
		}

		BevelBorder& BevelBorder::operator=(const BevelBorder &rhs)
		{
			BevelBorder temp(rhs);
			swap(temp);
			return *this;
		}

		void BevelBorder::swap(BevelBorder& rhs) throw()
		{
			std::swap(isRaised,rhs.isRaised);
		}

		void BevelBorder::setType(int type)
		{
			isRaised = type;
		}
		
		int BevelBorder::getType() const 
		{
			return isRaised;
		}

		void BevelBorder::paintBorder(const Component* component, Graphics& g, int x, int y, int w, int h) const
		{
			if(isRaised == RAISED)
			{
				paintRaisedBorder(g,x,y,w,h);
			}
			else if(isRaised == LOWERED)
			{
				paintLoweredBorder(g,x,y,w,h);
			}
		}

		void BevelBorder::paintLoweredBorder(Graphics& g,int x, int y, int w,int h) const
		{
			/**
			 * Hard BevelBorder, without soft edges.
			 */

			// adjust for opengl
			y += 1;
			//w -= 1;
			//h -= 1;
			
			g.setPaint(&loweredShadow);
			g.drawRect(x,y,w-1,h-1);

			g.setPaint(&loweredHighlight);
			g.drawRect(x+1,y+1,w-1,h-1);
		}

		void BevelBorder::paintRaisedBorder(Graphics& g, int x, int y, int w, int h) const
		{
			/**
			 * Hard BevelBorder, without soft edges.
			 */
			// adjust for opengl
			y += 1;
			//w -= 1;
			//h -= 1;
			
			g.setPaint(&raisedShadow);
			g.drawRect(x,y,w-1,h-1);

			g.setPaint(&raisedHighlight);
			g.drawRect(x+1,y+1,w-1,h-1);
		}

		const util::Insets BevelBorder::getBorderInsets() const
		{
			return util::Insets(2,2,2,2);
		}
	}
}