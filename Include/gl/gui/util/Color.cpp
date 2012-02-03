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
#include "./Color.h"

namespace ui
{
	namespace util
	{

		Color::Color(int redValue, int greenValue, int blueValue)
		{
			init(redValue,greenValue,blueValue,255);
		}

		Color::Color(int redValue, int greenValue, int blueValue, int alphaValue)	
		{
			init(redValue,greenValue,blueValue,alphaValue);
		}

		Color::Color(float redValue, float greenValue, float blueValue)
		{
			init(redValue,greenValue,blueValue,1.0f);
		}
		
		Color::Color(float redValue, float greenValue, float blueValue, float alphaValue)
		{
			init(redValue,greenValue,blueValue,alphaValue);
		}

		void Color::init(int redValue,int greenValue, int blueValue, int alphaValue)
		{
			init((float)redValue/255,(float)greenValue/255,(float)blueValue/255,(float)alphaValue/255);
		}

		void Color::init(float redValue, float greenValue, float blueValue, float alphaValue)
		{
			red = redValue;
			green = greenValue;
			blue = blueValue;
			alpha = alphaValue;
		}

		float Color::getAlpha(int point) const
		{
			return alpha;
		}

		float Color::getBlue(int point) const
		{
			return blue;
		}

		float Color::getGreen(int point) const
		{
			return green;
		}

		float Color::getRed(int point) const
		{
			return red;
		}

		Color::~Color()
		{
		}

		Color::Color()
		{
			init(0.0f,0.0f,0.0f,0.0f);
		}

		Color::Color(const Color& rhs)
		{
			red = rhs.red;
			green = rhs.green;
			blue = rhs.blue;
			alpha = rhs.alpha;	
		}

		Color& Color::operator =(const Color& rhs)
		{
			if(this == &rhs)
				return *this;
			
			red = rhs.red;
			green = rhs.green;
			blue = rhs.blue;
			alpha = rhs.alpha;

			return *this;
		}

		bool Color::operator ==(const Color& rhs)
		{
			return ((red == rhs.red) && (blue == rhs.blue) && (green == rhs.green) && (alpha == rhs.alpha));
		}
	}
}