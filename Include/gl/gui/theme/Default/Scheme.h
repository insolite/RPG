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
#ifndef SCHEME_H
#define SCHEME_H

#include "../../util/Paint.h"
#include "../../Font.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class Scheme
			{
			public:
				virtual util::Paint * getTitleBarSelected() const = 0;
				virtual util::Paint * getTitleBarDeselected() const = 0;
				virtual util::Paint * getPushableRaisedBackground() const = 0;
				virtual util::Paint * getPushableLoweredBackground() const = 0;
				virtual util::Paint * getDefaultBackground() const = 0;
				virtual util::Paint * getTextBackground()  const = 0;
				virtual util::Paint * getTextColor() const = 0;
				virtual util::Paint * getMenuBarBackground() const = 0;
				virtual util::Paint * getHighlight() const = 0;

				virtual util::Paint * getMenuSelectedBackground()  const = 0;
				virtual util::Paint * getMenuDeselectedBackground() const = 0;

				virtual Font * getDefaultFont() const = 0;

				virtual ~Scheme() {};

			};

			class SchemeManager
			{
			public:

				static SchemeManager &getInstance()
				{
					static SchemeManager obj;
					return obj;
				}
				Scheme * getScheme() const;
				void setScheme(Scheme *s);
			private:
				SchemeManager();
				~SchemeManager();
				SchemeManager(const SchemeManager&);
				SchemeManager& operator=(const SchemeManager&);
				Scheme *scheme;
			};
		}
	}
}

#endif