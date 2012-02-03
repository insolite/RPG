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
#include "./ToggleButtonTheme.h"
#include "../../Component.h"
#include "../../component/ToggleButton.h"
#include "../../Graphics.h"
#include "../../event/PropertyEvent.h"
#include "../../GlyphContext.h"
#include "./Util.h"
#include "../../event/KeyEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			ToggleButtonTheme::ToggleButtonTheme()
				:
					backgroundRaised(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_180),
					backgroundLowered(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0),
					borderRaised(border::BevelBorder::RAISED),
					borderLowered(border::BevelBorder::LOWERED),
					foreground(0,0,0)
			{
			}

			void ToggleButtonTheme::installTheme(Component *comp)
			{
				ToggleButton *button = static_cast<ToggleButton*>(comp);

				button->addPropertyListener(this);
				if(button->isSelected())
				{
					button->setBorder(&borderLowered);
					button->setBackground(SchemeManager::getInstance().getScheme()->getPushableLoweredBackground());
				}
				else
				{
					button->setBorder(&borderRaised);
					button->setBackground(SchemeManager::getInstance().getScheme()->getPushableRaisedBackground());
				}
				button->setBorderPainted(true);
				button->setForeground(&foreground);
				button->setMargin(util::Insets(7,7,7,7));
				button->addKeyListener(this);
				button->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void ToggleButtonTheme::deinstallTheme(Component *comp)
			{
				ToggleButton *button = static_cast<ToggleButton*>(comp);

				button->removePropertyListener(this);
				button->removeKeyListener(this);
			}

			void ToggleButtonTheme::paint(Graphics &g, const Component *comp) const
			{
				const ToggleButton *button = static_cast<const ToggleButton*>(comp);

				if(button->isContentAreaFilled())
				{
					ComponentTheme::paint(g,button);
				}
				Util::paintButton(button,g);
			}

			void ToggleButtonTheme::propertyChanged(const event::PropertyEvent &e)
			{
				if(e.getClassID() == event::PropertyEvent::SPECIAL)
				{
					int id = e.getID();

					ToggleButton *comp = static_cast<ToggleButton*>(e.getSource());

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
					}
				}
			}

			const util::Dimension ToggleButtonTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				return Util::getButtonSize(button);
			}

			
			void ToggleButtonTheme::keyPressed(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doPressed();
				}
			}

			void ToggleButtonTheme::keyReleased(const event::KeyEvent &e)
			{
				if(e.getKeyCode() == event::KeyEvent::VKUI_SPACE)
				{
					AbstractButton *button = static_cast<AbstractButton*>(e.getSource());
					button->doReleased();
				}
			}

			void ToggleButtonTheme::keyTyped(const event::KeyEvent &e)
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