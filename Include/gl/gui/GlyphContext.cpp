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
#include "./GlyphContext.h"
#include "./Font.h"

namespace ui
{
	
	GlyphContext::GlyphContext()
		:	fontFactory(0)
	{
	}

	GlyphContext::~GlyphContext()
	{
		fontList.clear();
	}
	

	Font* GlyphContext::getFont(std::size_t index) const
	{
		// If your debugger points to this, it is most
		// likely you are trying to use a font without
		// a font being present. Please make sure you
		// set a font for every Component that needs one.
		return fontList.at(index);
	}

	Font* GlyphContext::createFont(const std::string &fontname, std::size_t size)
	{
		// fontFactory cannot be NULL. You must create an AbstractFontFactory and
		// call GlyphContext::getInstance().setFontFactory(yourFactory);
		// See the documentation for more information.
		assert(fontFactory);

		for(std::size_t i = 0; i < fontList.size(); ++i)
		{
			if(fontList[i]->getFontName() == fontname && fontList[i]->getSize() == size)
			{
				return fontList.at(i);
			}
		}
		return fontFactory->createFont(fontname,size);
	}

	void GlyphContext::setFontFactory(AbstractFontFactory *factory)
	{
		fontFactory = factory;
	}

	AbstractFontFactory * GlyphContext::getFontFactory() const
	{
		return fontFactory;
	}

	std::size_t GlyphContext::setFont(Font* font)
	{
		for(std::size_t i = 0; i < fontList.size(); ++i)
		{
			if(fontList[i] == font)
			{
				return i;
			}
		}
		fontList.push_back(font);
		
		return fontList.size() - 1;
	}
}