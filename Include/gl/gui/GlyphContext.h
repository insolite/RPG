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

#ifndef GLYPHCONTEXT_H
#define GLYPHCONTEXT_H

#include "./Pointers.h"
#include "./Font.h"

namespace ui
{

	/**
	 * A singleton class which manages the Font
	 * instances. This is to prevent the Components
	 * from creating their own Font class each time.
	 */
	class GlyphContext
	{
	public:
		/**
		 * Stores or sets an indexed font.
		 * @param
		 * font the Font to use as current (is this even english?).
		 * @return
		 * the index used for this Font, or a new index if the Font wasn't used before.
		 */
		std::size_t setFont(Font* font);

		/**
		 * Returns the indexed Font.
		 * @param
		 *	index the font stored in a Component.
		 * @return
		 *	the Font stored on the index.
		 */
		Font* getFont(std::size_t index) const;

		/**
		 * Creates a new Font, based on a fontname, style and size.
		 * @param
		 *	fontname Font family name, such as 'Arial'
		 * @param
		 *	size the Font size in points.
		 * @return
		 * A pointer to the newly created Font.
		 */
		Font* createFont(const std::string &fontname, std::size_t size);

		/**
		 * Sets the FontFactory to be used by GlyphContext.
		 * A FontFactory creates font based on certain parameters.
		 */
		void setFontFactory(AbstractFontFactory *factory);

		/**
		 * Returns the FontFactory currently in use.
		 */
		AbstractFontFactory * getFontFactory() const;

		/**
		 * Returns an instance of this class.
		 * @note this is part of the Singleton.
		 */
		static GlyphContext &getInstance()
		{
			static GlyphContext obj;
			return obj;
		}
	private:
		GlyphContext();
		~GlyphContext();
		GlyphContext(const GlyphContext&);
		GlyphContext& operator=(const GlyphContext&);
		FontList fontList;
		AbstractFontFactory *fontFactory;
	};
}
#endif