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
#include "./RadioButtonTheme.h"
#include "../../Component.h"
#include "../../component/ToggleButton.h"
#include "./Util.h"
#include "../../Graphics.h"
#include "../../Font.h"
#include "../../GlyphContext.h"
#include "../../event/KeyEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			RadioButtonTheme::RadioButtonTheme()
				:	foreground(0,0,0)
			{
			}

			void RadioButtonTheme::deinstallTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->removePropertyListener(this);
				button->removeKeyListener(this);
			}

			void RadioButtonTheme::installTheme(Component *comp)
			{
				ToggleButton *button = static_cast<ToggleButton*>(comp);
				button->addPropertyListener(this);
				button->setContentAreaFilled(false);
				button->setDefaultIcon(&defaultIcon);
				button->setSelectedIcon(&selectedIcon);
				button->setMargin(util::Insets(7,7,7,7));
			//	button->setForeground(&foreground);
				button->setHorizontalAlignment(Component::LEFT);
				button->setBorder(NULL);
				button->addKeyListener(this);
				button->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void RadioButtonTheme::paint(Graphics &g, const Component *comp) const
			{
				const ToggleButton *button = static_cast<const ToggleButton*>(comp);

				if(button->isContentAreaFilled())
				{
					ComponentTheme::paint(g,button);
				}
				Util::paintButton(button,g);
			}

			const util::Dimension RadioButtonTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			void RadioButtonTheme::propertyChanged(const event::PropertyEvent &e)
			{
			}

			
			void RadioButtonTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void RadioButtonTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void RadioButtonTheme::keyTyped(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doClicked();
				}
			}

		// -------------------------------------------------------------------

			int RadioButtonTheme::DefaultIcon::getIconHeight() const
			{
				return 20;
			}

			int RadioButtonTheme::DefaultIcon::getIconWidth() const
			{
				return 20;
			}

			void RadioButtonTheme::DefaultIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				int spacing = 3;
				int border = 1;

				int xbase = x + 10;
				int ybase = y + 10;
				int radius = getIconWidth() - spacing - spacing - border - border;

				g.setPaint(&background);
				g.fillCircle(xbase,ybase,radius);
				g.setPaint(&foreground);
				g.fillCircle(xbase,ybase,radius - border);
			}

			RadioButtonTheme::DefaultIcon::DefaultIcon()
				:	foreground(255,255,255),
					background(0,0,0)
			{
			}

// -------------------------------------------------------------------

			int RadioButtonTheme::SelectedIcon::getIconHeight() const
			{
				return 20;
			}

			int RadioButtonTheme::SelectedIcon::getIconWidth() const
			{
				return 20;
			}

			void RadioButtonTheme::SelectedIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				int spacing = 3;
				int border = 1;

				int xbase = x + 10;
				int ybase = y + 10;
				int radius = getIconWidth() - spacing - spacing - border - border;

				g.setPaint(&background);
				g.fillCircle(xbase,ybase,radius);
				g.setPaint(&foreground);
				g.fillCircle(xbase,ybase,radius - border);

				g.setPaint(&background);
				g.fillCircle(xbase,ybase,radius - border - spacing - border);
			}

			RadioButtonTheme::SelectedIcon::SelectedIcon()
				:	foreground(255,255,255),
					background(0,0,0)
			{
			}

		}
	}
}