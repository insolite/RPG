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
#include "./GradientColor.h"

namespace ui
{
	namespace util
	{
		GradientColor::GradientColor(const Color& c1, const Color& c2, int direction)
		{
			color1 = c1;
			color2 = c2;
			dir = direction;
		}

		GradientColor::GradientColor(const Color& c1, const Color& c2)
		{
			color1 = c1;
			color2 = c2;
			dir = GradientColor::DEGREES_0;
		}

		float GradientColor::getAlpha(int point) const
		{
			return getColor(point).alpha;
		}

		const Color & GradientColor::getColor(int point) const
		{
			if(dir == GradientColor::DEGREES_0)
			{
				switch(point)
				{
				case Paint::UPPERLEFT:
					{
						return color1;
						break;
					}
				case Paint::UPPERRIGHT:
					{
						return color1;
						break;
					}
				case Paint::LOWERRIGHT:
					{
						return color2;
						break;
					}
				case Paint::LOWERLEFT:
					{
						return color2;
						break;
					}
				}
			}
			else if(dir == GradientColor::DEGREES_90)
			{
				switch(point)
				{
				case Paint::UPPERLEFT:
					{
						return color2;
						break;
					}
				case Paint::UPPERRIGHT:
					{
						return color1;
						break;
					}
				case Paint::LOWERRIGHT:
					{
						return color1;
						break;
					}
				case Paint::LOWERLEFT:
					{
						return color2;
						break;
					}
				}
			}
			else if(dir == GradientColor::DEGREES_180)
			{
				switch(point)
				{
				case Paint::UPPERLEFT:
					{
						return color2;
						break;
					}
				case Paint::UPPERRIGHT:
					{
						return color2;
						break;
					}
				case Paint::LOWERRIGHT:
					{
						return color1;
						break;
					}
				case Paint::LOWERLEFT:
					{
						return color1;
						break;
					}
				}
			}
			else if(dir == GradientColor::DEGREES_270)
			{
				switch(point)
				{
				case Paint::UPPERLEFT:
					{
						return color1;
						break;
					}
				case Paint::UPPERRIGHT:
					{
						return color2;
						break;
					}
				case Paint::LOWERRIGHT:
					{
						return color2;
						break;
					}
				case Paint::LOWERLEFT:
					{
						return color1;
						break;
					}
				}
			}

			return color1;
		}

		float GradientColor::getRed(int point) const
		{
			return getColor(point).red;
		}

		float GradientColor::getGreen(int point) const
		{
			return getColor(point).green;
		}

		float GradientColor::getBlue(int point) const
		{
			return getColor(point).blue;
		}
	}
}