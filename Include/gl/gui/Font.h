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

#ifndef FONT_H
#define FONT_H

#include "./util/Dimension.h"

namespace ui
{
	/**
	 * Defines a Font to be used by the GUI.
	 * Font is an abstract base class for writing
	 * system specific font classes.
	 */
	class Font
	{
	public:
		/** 
		 * Returns the font name.
		 */
		virtual const std::string getFontName() const = 0;
		/**
		 * Returns the point size of this Font.
		 */
		virtual std::size_t getSize() const = 0;

		/**
		 * Returns the bounding box for this Font, given a 
		 * string.
		 * @return
		 *	the bounding box of the string in pixel units.
		 */
		virtual util::Dimension getStringBoundingBox(const std::string &text) const = 0;

		/**
		 * Draws a string at the specified location.
		 */
		virtual void drawString(int x, int y, const std::string &text) = 0;

		/**
		 * Destructor.
		 */
		virtual ~Font();

		/**
		 * Compare two fonts.
		 */
		bool operator==(const Font &rhs);
	};

	/**
	 * AbstractFontFactory creates Fonts.
	 * The user overloads this abstract class for his or
	 * her own Font class so that GlyphContext can create
	 * user defined fonts.
	 * 
	 */
	class AbstractFontFactory
	{
	public:
		/**
		 * Create a Font.
		 * @note Note that the user of the library is responsible for
		 * maintaining memory, as such, memory allocated here must also
		 * be deallocated.
		 */
		virtual Font * createFont(const std::string &font, std::size_t size) = 0;

		/**
		 * Destructor.
		 */
		virtual ~AbstractFontFactory();
	};
}
#endif