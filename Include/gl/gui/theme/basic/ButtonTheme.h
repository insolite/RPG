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

#ifndef BASICBUTTONTHEME_H
#define BASICBUTTONTHEME_H

#include "./ComponentTheme.h"
#include "../../border/LineBorder.h"
#include "../../event/PropertyListener.h"
#include "../../component/AbstractButton.h"
#include "../TextUtil.h"
namespace ui
{
	namespace theme
	{
		namespace basic
		{
			class ButtonTheme : public BasicComponent, public event::PropertyListener
			{
			public:
				ButtonTheme();
				virtual void installTheme(Component *comp);
				virtual void deinstallTheme(Component *comp);
				virtual void paint(Graphics& g,const Component *comp) const;
				virtual const util::Dimension getPreferredSize(const Component *comp) const;
				virtual void propertyChanged(const event::PropertyEvent &e);
				virtual void paintFocus(int x, int y, Graphics &g, const util::Dimension &componentBoundingBox, const util::Dimension &boundingBox, int spacing) const;
				virtual void paintButton(int x, int y, Graphics &g, const StringInfoBuffer &buffer, const util::Dimension &stringBoundingBox ,int alignment, Icon *icon) const;

			protected:
				Icon * getActiveIcon(const AbstractButton *button) const;
				util::Color black;
				util::Color	white;
				border::LineBorder border;
				CuttoffAlgorithm algorithm;
				TextUtil textUtil;
				
			};
		}
	}
}

#endif