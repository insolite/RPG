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
#ifndef DEFAULTSCHEME_H
#define DEFAULTSCHEME_H

#include "./Scheme.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class DefaultScheme : public Scheme
			{
			public:
				DefaultScheme();
				~DefaultScheme();
				virtual util::Paint * getTitleBarSelected() const;
				virtual util::Paint * getTitleBarDeselected() const;
				virtual util::Paint * getPushableRaisedBackground() const;
				virtual util::Paint * getPushableLoweredBackground() const;
				virtual util::Paint * getDefaultBackground() const;
				virtual util::Paint * getTextBackground()  const;
				virtual util::Paint * getTextColor() const;
				virtual util::Paint * getMenuBarBackground() const;
				virtual util::Paint * getHighlight() const;

				virtual util::Paint * getMenuSelectedBackground() const;
				virtual util::Paint * getMenuDeselectedBackground() const;

				virtual Font * getDefaultFont() const;
			private:
				util::Paint * titleBarSelected;
				util::Paint * titleBarDeselected;
				util::Paint * pushableRaisedBackground;
				util::Paint * pushableLoweredBackground;
				util::Color * defaultBackground;
				util::Color * textColor;
				util::Paint * textBackground;
				util::Paint * menuBarBackground;
				util::Paint * highlight;
				util::Paint * menuSelectedBackground;
				util::Paint * menuDeselectedBackground;

				Font * defaultFont;
			};
		}
	}
}

#endif