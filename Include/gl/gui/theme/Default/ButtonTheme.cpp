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
#include "./ButtonTheme.h"
#include "../../Component.h"
#include "../../component/AbstractButton.h"
#include "../../Graphics.h"
#include "../../event/PropertyEvent.h"
#include "../../Font.h"
#include "../../GlyphContext.h"
#include "./Util.h"
#include "../../event/KeyEvent.h"


namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			ButtonTheme::ButtonTheme()
				:
					backgroundRaised(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0),
					backgroundLowered(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0),
					borderRaised(border::BevelBorder::RAISED),
					borderLowered(border::BevelBorder::LOWERED),
					foreground(0,0,0),
					focus(139,178,206)
			{
			}

			void ButtonTheme::installTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->addPropertyListener(this);
				button->setBorder(&borderRaised);
				button->setBackground(SchemeManager::getInstance().getScheme()->getPushableRaisedBackground());
				button->setForeground(SchemeManager::getInstance().getScheme()->getTextColor());
				button->setBorderPainted(true);
				button->setFocusPainted(true);
				button->setMargin(util::Insets(7,7,7,7));
				button->addKeyListener(this);
				button->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void ButtonTheme::deinstallTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->removePropertyListener(this);
				button->removeKeyListener(this);
			}

			void ButtonTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				Util::paintButton(button,g);

			}

			void ButtonTheme::propertyChanged(const event::PropertyEvent &e)
			{
				if(e.getClassID() == event::PropertyEvent::SPECIAL)
				{
					int id = e.getID();

					AbstractButton *comp = static_cast<AbstractButton*>(e.getSource());

					switch(id)
					{
					case AbstractButton::FOCUSPAINTCHANGED:
						{
							break;
						}	
					case AbstractButton::SELECTED:
						{
				
								comp->setBackground(SchemeManager::getInstance().getScheme()->getPushableLoweredBackground());
								comp->setBorder(&borderLowered);
							
							break;
						}
					case AbstractButton::DESELECTED:
						{
						
								comp->setBackground(SchemeManager::getInstance().getScheme()->getPushableRaisedBackground());
								comp->setBorder(&borderRaised);
				
							break;
						}
					case AbstractButton::TEXTCHANGE:
						{
							break;
						}
					}
				}
			}

			const util::Dimension ButtonTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			void ButtonTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void ButtonTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void ButtonTheme::keyTyped(const event::KeyEvent &e)
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