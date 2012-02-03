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

#ifndef MENUTHEME_H
#define MENUTHEME_H

#include "./ComponentTheme.h"
#include "../../util/GradientColor.h"
#include "../../event/PropertyListener.h"
#include "../../border/LineBorder.h"
#include "../../event/KeyListener.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class MenuTheme : public ComponentTheme, public event::PropertyListener, public event::KeyListener
			{
			public:
				MenuTheme();
				void installTheme(Component *comp);
				void deinstallTheme(Component *comp);
				void paint(Graphics& g,const Component *comp) const;
				const util::Dimension getPreferredSize(const Component *comp) const;
				void propertyChanged(const event::PropertyEvent &e);
			private:
				void keyTyped(const event::KeyEvent &e);
				void keyPressed(const event::KeyEvent &e);
				void keyReleased(const event::KeyEvent &e);
				util::GradientColor background;
				util::Color foreground;
				border::LineBorder border;
				util::Color transparant;
			};
		}
	}
}

#endif