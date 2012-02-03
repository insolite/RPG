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

#ifndef COLOR_H
#define COLOR_H

#include "../Pointers.h"
#include "./Paint.h"

namespace ui
{
	namespace util
	{
		/**
		* Defines a datatype for Color information.
		* Currently supports only the RGBA color space,
		* with floating point precision.
		*/
		class Color : public Paint
		{
		private:
			void init(int redValue, int greenValue, int blueValue, int alphaValue);
			void init(float redValue, float greenValue, float blueValue, float alphaValue);
		public:
			/**
			* Creates a new color with given red, green, blue and alpha values.
			* @param
			* redValue the red value ranging from 0-1.
			* @param
			* blueValue the blue value ranging from 0-1.
			* @param
			* greenValue the red value ranging from 0-1.
			* @param
			* alphaValue the alpha valua ranging from 0-1.
			*/
			Color(float redValue, float greenValue, float blueValue, float alphaValue);

			/**
			* Creates a new color with given red, green, blue values.
			* @param
			* redValue the red value ranging from 0-1.
			* @param
			* blueValue the blue value ranging from 0-1.
			* @param
			* greenValue the red value ranging from 0-1.
			*/
			Color(float redValue, float greenValue, float blueValue);

			/**
			* Creates a new color with given red, green, blue values.
			* @param
			* redValue the red value ranging from 0-255.
			* @param
			* blueValue the blue value ranging from 0-255.
			* @param
			* greenValue the red value ranging from 0-255.
			*/
			Color(int redValue, int greenValue, int blueValue);

			/**
			* Creates a new color with given red, green, blue values.
			* @param
			* redValue the red value ranging from 0-255.
			* @param
			* blueValue the blue value ranging from 0-255.
			* @param
			* greenValue the red value ranging from 0-255.
			* @param
			* alphaValue the alpha value ranging from 0-255.
			*/
			Color(int redValue, int greenValue, int blueValue, int alphaValue);
			~Color();


			/**
			* The red component ranging from 0 to 1.
			*/
			float red;
			
			/**
			* The blue component ranging from 0 to 1.
			*/
			float blue;

			/**
			* The green component ranging from 0 to 1.
			*/
			float green;

			/**
			* The alpha component ranging from 0 to 1.
			*/
			float alpha;

			float getRed(int point) const;
			float getGreen(int point) const;
			float getBlue(int point) const;
			float getAlpha(int point) const;

			bool operator==(const Color& rhs);
		
			Color& operator=(const Color& rhs);

			Color();
			Color(const Color& rhs);
		};
	}
}
#endif