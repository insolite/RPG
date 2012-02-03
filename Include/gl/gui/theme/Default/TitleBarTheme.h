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
#ifndef TITLEBARTHEME_H
#define TITLEBARTHEME_H

#include "./ComponentTheme.h"
#include "../../Graphics.h"
#include "../../Icon.h"
#include "../../layout/BorderLayout.h"
#include "../../component/Button.h"
#include "../../component/TitleBar.h"
#include "../../util/Color.h"
#include "../../util/GradientColor.h"
#include "../../border/LineBorder.h"
#include "../../event/MouseListener.h"
#include "../../event/MouseEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class TitleBarTheme :	public ComponentTheme, public event::MouseAdapter
			{
			public:
				TitleBarTheme();
				void installTheme(Component *comp);
				void deinstallTheme(Component *comp);
			private:
				class CloseIcon : public Icon
				{
				public:
					CloseIcon();
					int getIconHeight() const;
					int getIconWidth() const;
					void paint(const Component *comp, Graphics &g, int x, int y) const;
				private:
					util::Color foreground;
				};

				CloseIcon closeIcon;

				util::GradientColor background;
				util::Color foreground;
				util::Color borderColor;
				border::LineBorder border;

				//void mouseClicked(const event::MouseEvent &e);
				//void mouse
			};
		}
	}
}

#endif