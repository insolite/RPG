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

#ifndef BASICCOMPONENTTHEME_H
#define BASICCOMPONENTTHEME_H

#include "../ThemeComponent.h"
#include "../../util/Color.h"
#include "../../util/Dimension.h"

//#include "./Scheme.h"

namespace ui
{
	namespace theme
	{
		namespace basic
		{
			/**
			 * Default component theme, not to be confused with
			 * the ComponentTheme interface. Yea, I really need
			 * better names.
			 */
			class BasicComponent : public ThemeComponent
			{
			public:
				BasicComponent();
				virtual ~BasicComponent();
				virtual void installTheme(Component *comp);
				virtual void deinstallTheme(Component *comp);
				virtual void paint(Graphics& g, const Component *comp) const;
				virtual void paintSelection(Graphics &g, const Component *comp) const;
				virtual const util::Dimension getPreferredSize(const Component *comp) const;
				void setPreferredSize(const util::Dimension& size);
			private:
				util::Color defaultBackground;
				util::Color defaultForeground;
			};
		}
	}
}

#endif