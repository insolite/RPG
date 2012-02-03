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
#include "./CheckBoxTheme.h"
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
			CheckBoxTheme::CheckBoxTheme()
				:	foreground(0,0,0)
			{
			}

			void CheckBoxTheme::deinstallTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->removePropertyListener(this);
				button->removeKeyListener(this);
			}

			void CheckBoxTheme::installTheme(Component *comp)
			{
				ToggleButton *button = static_cast<ToggleButton*>(comp);
				button->addPropertyListener(this);
				button->setContentAreaFilled(false);
				button->setDefaultIcon(&defaultIcon);
				button->setSelectedIcon(&selectedIcon);
				button->setMargin(util::Insets(7,7,7,7));
				button->setForeground(SchemeManager::getInstance().getScheme()->getTextColor());
				button->setHorizontalAlignment(Component::LEFT);
				button->setBorder(NULL);
				button->addKeyListener(this);
				button->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void CheckBoxTheme::paint(Graphics &g, const Component *comp) const
			{
				const ToggleButton *button = static_cast<const ToggleButton*>(comp);

				if(button->isContentAreaFilled())
				{
					ComponentTheme::paint(g,button);
				}
				Util::paintButton(button,g);
			}

			const util::Dimension CheckBoxTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			void CheckBoxTheme::propertyChanged(const event::PropertyEvent &e)
			{
			}

			
			void CheckBoxTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void CheckBoxTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void CheckBoxTheme::keyTyped(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doClicked();
				}
			}

		// -------------------------------------------------------------------

			int CheckBoxTheme::DefaultIcon::getIconHeight() const
			{
				return 20;
			}

			int CheckBoxTheme::DefaultIcon::getIconWidth() const
			{
				return 20;
			}

			void CheckBoxTheme::DefaultIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				int spacing = 4;
				int border = 1;
				g.setPaint(&background);
				g.fillRect(x + spacing,y + spacing,getIconWidth() - spacing - spacing,getIconHeight() - spacing - spacing);
				g.setPaint(&foreground);
				g.fillRect(x + spacing + border,y + spacing + border, getIconWidth() - spacing - spacing - border - border, getIconHeight() - spacing - spacing - border - border);
			}

			CheckBoxTheme::DefaultIcon::DefaultIcon()
				:	foreground(255,255,255),
					background(0,0,0)
			{
			}

// -------------------------------------------------------------------

			int CheckBoxTheme::SelectedIcon::getIconHeight() const
			{
				return 20;
			}

			int CheckBoxTheme::SelectedIcon::getIconWidth() const
			{
				return 20;
			}

			void CheckBoxTheme::SelectedIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				int spacing = 4;
				int border = 1;
				g.setPaint(&background);
				g.fillRect(x + spacing,y + spacing,getIconWidth() - spacing - spacing,getIconHeight() - spacing - spacing);
				g.setPaint(&foreground);
				g.fillRect(x + spacing + border,y + spacing + border, getIconWidth() - spacing - spacing - border - border, getIconHeight() - spacing - spacing - border - border);

				g.setPaint(&background);
				int xbase = x + spacing + border;
				int ybase = y + spacing + border;
				g.setLineWidth(2);
				g.drawLine(xbase, ybase, xbase + getIconWidth() - spacing - spacing - border - border, ybase + getIconHeight() - spacing - spacing - border - border);
				g.drawLine(xbase + getIconWidth() - spacing - spacing - border - border, ybase, xbase, ybase + getIconHeight() - spacing - spacing - border - border);
				g.setLineWidth(1);
			}

			CheckBoxTheme::SelectedIcon::SelectedIcon()
				:	foreground(255,255,255),
					background(0,0,0)
			{
			}

		}
	}
}