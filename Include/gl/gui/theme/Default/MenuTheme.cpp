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
#include "./MenuTheme.h"
#include "../../Component.h"
#include "../../GlyphContext.h"
#include "./Util.h"
#include "../../Graphics.h"
#include "../../event/PropertyEvent.h"
#include "../../component/Menu.h"
#include "../../event/KeyEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			MenuTheme::MenuTheme()
				:	background(util::Color(137,137,155), util::Color(192,192,206),util::GradientColor::DEGREES_0),
					foreground(0,0,0),
					border(util::Color(128,128,128)),
					transparant(0,0,0,0)
			{
			}

			void MenuTheme::installTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->setFocusPainted(false);
				button->setBorder(&border);
				button->setBackground(SchemeManager::getInstance().getScheme()->getMenuDeselectedBackground());
				button->setBorderPainted(false);
				button->setForeground(&foreground);
				button->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
				button->addPropertyListener(this);
				button->addKeyListener(this);

			}

			void MenuTheme::deinstallTheme(Component *comp)
			{
				comp->removePropertyListener(this);
				comp->removeKeyListener(this);
			}

			void MenuTheme::propertyChanged(const event::PropertyEvent &e)
			{
				if(e.getClassID() == event::PropertyEvent::SPECIAL)
				{
					if(e.getID() == Menu::SELECTED)
					{
						e.getSource()->setBorderPainted(true);
						e.getSource()->setBackground(SchemeManager::getInstance().getScheme()->getMenuSelectedBackground());
					}
					else if(e.getID() == Menu::DESELECTED)
					{
						e.getSource()->setBorderPainted(false);
						e.getSource()->setBackground(SchemeManager::getInstance().getScheme()->getMenuDeselectedBackground());
					}
				}
			}

			void MenuTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				Util::paintButton(button,g);
			}

			const util::Dimension MenuTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			void MenuTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void MenuTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void MenuTheme::keyTyped(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doClicked();
				}
			}

		}
	}
}