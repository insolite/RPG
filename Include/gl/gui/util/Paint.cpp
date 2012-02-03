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
#include "./Paint.h"

namespace ui
{
	namespace util
	{
		Paint::Paint()
		{
		}

		Paint::~Paint()
		{
		}

		float Paint::getAlpha(int point) const
		{
			return 0.0f;
		}

		float Paint::getRed(int point) const
		{
			return 0.0f;
		}

		float Paint::getGreen(int point) const
		{
			return 0.0f;
		}

		float Paint::getBlue(int point) const
		{
			return 0.0f;
		}

		float LighterPaint::getAlpha(int point) const
		{
			return color->getAlpha(point);
		}

		float LighterPaint::getBlue(int point) const
		{
			return color->getBlue(point) + 0.5f;
		}

		float LighterPaint::getGreen(int point) const
		{
			return color->getGreen(point) + 0.5f;
		}

		float LighterPaint::getRed(int point) const
		{
			return color->getRed(point) + 0.5f;
		}

		LighterPaint::LighterPaint(const Paint *c)
			:	color(c)
		{
		}

		float DarkerPaint::getAlpha(int point) const
		{
			return color->getAlpha(point);
		}

		float DarkerPaint::getBlue(int point) const
		{
			return color->getBlue(point) - 0.5f;
		}

		float DarkerPaint::getGreen(int point) const
		{
			return color->getGreen(point) - 0.5f;
		}

		float DarkerPaint::getRed(int point) const
		{
			return color->getRed(point) - 0.5f;
		}

		DarkerPaint::DarkerPaint(const Paint *c)
			:	color(c)
		{
		}
	}
}