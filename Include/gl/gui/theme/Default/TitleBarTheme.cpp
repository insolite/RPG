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
#include "./TitleBarTheme.h"
#include "../../component/Button.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			TitleBarTheme::TitleBarTheme()

				:	background(util::Color(224,224,224),util::Color(180,180,180),util::GradientColor::DEGREES_90),
					borderColor(128,128,128),
					border(borderColor,1), // is this dangerous? initialization order?
					foreground(0,0,0)
			{
			}

			void TitleBarTheme::installTheme(Component *comp)
			{
				TitleBar * titleBar = static_cast<TitleBar*>(comp);
				titleBar->getCloseButton()->setDefaultIcon(&closeIcon);
				titleBar->getCloseButton()->setSelectedIcon(&closeIcon);
				titleBar->getCloseButton()->setMargin(util::Insets(0,0,0,0));
				titleBar->getCloseButton()->setFocusPainted(false);
				titleBar->getTitleLabel()->setMargin(util::Insets(0,5,0,0));
				//titleBar->getTitleLabel()->setForeground(&foreground);
				titleBar->setBackground(SchemeManager::getInstance().getScheme()->getTitleBarDeselected());
				titleBar->setBorder(&border);
				titleBar->setInsets(util::Insets(0,0,1,0)); // draw only the bottom border (looks better)
				titleBar->getTitleLabel()->setBackground(&background);
			}

			void TitleBarTheme::deinstallTheme(Component *comp)
			{
			}

// -------------------------------------------------------------------

			TitleBarTheme::CloseIcon::CloseIcon()
				:	foreground(0,0,0)
			{

			}

			int TitleBarTheme::CloseIcon::getIconHeight() const
			{
				return 15;
			}

			int TitleBarTheme::CloseIcon::getIconWidth() const
			{
				return 15;
			}

			void TitleBarTheme::CloseIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				int spacing = 2;
				int border = 1;

				g.setPaint(&foreground);
				int xbase = x + spacing + border;
				int ybase = y + spacing + border;
				g.setLineWidth(2);
				g.drawLine(xbase, ybase, xbase + getIconWidth() - spacing - spacing - border - border, ybase + getIconHeight() - spacing - spacing - border - border);
				g.drawLine(xbase + getIconWidth() - spacing - spacing - border - border, ybase, xbase, ybase + getIconHeight() - spacing - spacing - border - border);
				g.setLineWidth(1);
			}

		}
	}
}