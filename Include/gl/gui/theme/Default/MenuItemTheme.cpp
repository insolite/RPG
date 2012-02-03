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
#include "./MenuItemTheme.h"
#include "../../component/MenuItem.h"
#include "../../event/MouseEvent.h"
#include "../../GlyphContext.h"
#include "./Util.h"
#include "../../Graphics.h"
#include "../../event/FocusEvent.h"
#include "../../event/KeyEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			MenuItemTheme::MenuItemTheme()
				:	background(224,224,224),
					foreground(0,0,0),
					highlight(139,178,206)
			{
			}

			void MenuItemTheme::installTheme(Component *comp)
			{
				MenuItem * menuItem = static_cast<MenuItem*>(comp);

			//	menuItem->setBackground(&background);
			//	menuItem->setForeground(&foreground);
				menuItem->setHorizontalAlignment(Component::LEFT);
				menuItem->setMargin(util::Insets(6,6,6,6));
			//	menuItem->addMouseListener(this);
				menuItem->setFocusPainted(true);
			//	menuItem->addFocusListener(this);
				menuItem->addPropertyListener(this);
				menuItem->addKeyListener(this);
				menuItem->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void MenuItemTheme::deinstallTheme(Component *comp)
			{
				MenuItem * menuItem = static_cast<MenuItem*>(comp);
				menuItem->removePropertyListener(this);
				menuItem->removeKeyListener(this);
		//		menuItem->removeMouseListener(this);
		//		menuItem->removeFocusListener(this);
			}

			void MenuItemTheme::propertyChanged(const event::PropertyEvent &e)
			{
				
			}
/*
			void MenuItemTheme::mouseEntered(const event::MouseEvent &e)
			{
				e.getSource()->setBackground(&highlight);
				e.getSource()->setBorderPainted(true);
			}

			void MenuItemTheme::mouseExited(const event::MouseEvent &e)
			{
				e.getSource()->setBackground(&background);
				e.getSource()->setBorderPainted(false);
			}

			void MenuItemTheme::focusGained(const event::FocusEvent &e)
			{
				e.getSource()->setBackground(&highlight);
				e.getSource()->setBorderPainted(true);
			}

			void MenuItemTheme::focusLost(const event::FocusEvent &e)
			{
				e.getSource()->setBackground(&background);
				e.getSource()->setBorderPainted(false);
			}
*/
			void MenuItemTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const MenuItem *button = static_cast<const MenuItem*>(comp);

				Util::paintMenuItem(button,g);
			}

			const util::Dimension MenuItemTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			
			void MenuItemTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void MenuItemTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void MenuItemTheme::keyTyped(const event::KeyEvent &e)
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