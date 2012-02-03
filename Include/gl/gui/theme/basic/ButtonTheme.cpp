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
#include "../../Icon.h"


namespace ui
{
	namespace theme
	{
		namespace basic
		{
			ButtonTheme::ButtonTheme()
				:
					black(0,0,0),
					white(255,255,255),
					border(white,util::Insets(1,1,1,1)),
					textUtil(&algorithm)
			{
			}

			void ButtonTheme::installTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->addPropertyListener(this);
				button->setBorderPainted(true);
				button->setBorder(&border);
				button->setMargin(util::Insets(10,10,10,10));
				button->setFocusPainted(true);
				button->setFont(GlyphContext::getInstance().createFont("Vera.ttf",10)); // default font

				if(button->isSelected() && button->isContentAreaFilled())
				{
					util::Paint *background(button->getBackground());
					util::Paint *foreground(button->getForeground());
					button->setBackground(foreground);
					button->setForeground(background);
				}
			}

			void ButtonTheme::deinstallTheme(Component *comp)
			{
				AbstractButton *button = static_cast<AbstractButton*>(comp);

				button->removePropertyListener(this);
			}

			void ButtonTheme::paint(Graphics &g, const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				if(button->isContentAreaFilled())
				{
					BasicComponent::paint(g,button);
				}
				util::Dimension componentBoundingBox(button->getBounds().width,button->getBounds().height);
				util::Dimension iconBoundingBox(textUtil.getIconBoundingBox(getActiveIcon(button)));

				StringInfoBuffer stringInfo(textUtil.fitStringInBoundingBox(button->getText(),componentBoundingBox,iconBoundingBox,button->getFont(),button->getInsets(),button->getMargin()));

				util::Dimension stringBoundingBox(textUtil.getStringBoundingBox(stringInfo));

				int verticalIconAlignment = textUtil.getVerticalAlignment(iconBoundingBox,componentBoundingBox,button->getVerticalAlignment(),button->getInsets(),button->getMargin());
				int verticalTextAlignment = textUtil.getVerticalAlignment(stringBoundingBox,componentBoundingBox,button->getVerticalAlignment(),button->getInsets(),button->getMargin());
				int horizontalAlignment = textUtil.getHorizontalAlignment(stringBoundingBox,iconBoundingBox,componentBoundingBox,button->getHorizontalAlignment(),button->getInsets(),button->getMargin());

				if(getActiveIcon(button) != 0)
				{
					getActiveIcon(button)->paint(button,g,horizontalAlignment,verticalIconAlignment);
					horizontalAlignment += getActiveIcon(button)->getIconWidth();
				}

				g.setPaint(button->getForeground());
				g.setFont(button->getFont());

				if(button->hasFocus() && button->isFocusPainted())
				{
					paintFocus(horizontalAlignment,verticalTextAlignment,g,componentBoundingBox,stringBoundingBox,3);
				}

				if(getActiveIcon(button) != 0)
				{
					paintButton(horizontalAlignment,verticalTextAlignment,g,stringInfo,stringBoundingBox,Component::LEFT,getActiveIcon(button));
				}
				else
				{
					paintButton(horizontalAlignment,verticalTextAlignment,g,stringInfo,stringBoundingBox,Component::CENTER,getActiveIcon(button));
				}
			}

			void ButtonTheme::paintButton(int x, int y, Graphics &g, const StringInfoBuffer &buffer, const util::Dimension &stringBoundingBox ,int alignment, Icon *icon) const
			{
				StringInfoBuffer::const_iterator end(buffer.end());
				int height = 0;

				for(StringInfoBuffer::const_iterator iter = buffer.begin(); iter != end; ++iter)
				{
					int xloc = x;
					if(alignment == Component::CENTER)
					{
						xloc += (stringBoundingBox.width / 2) - ((*iter).second.width / 2);
					}
					else if(alignment == Component::RIGHT)
					{
						xloc += (stringBoundingBox.width - (*iter).second.width);
					}
					g.drawString(xloc,y + height,(*iter).first);
					height += (*iter).second.height;
				}
			}

			void ButtonTheme::paintFocus(int x, int y, Graphics &g, const util::Dimension &componentBoundingBox, const util::Dimension &boundingBox, int spacing) const
			{
				g.drawRect(x - spacing,y - spacing,boundingBox.width + spacing + spacing,boundingBox.height + spacing + spacing);
			}

			Icon * ButtonTheme::getActiveIcon(const AbstractButton *button) const
			{
				if(button->isSelected())
				{
					return button->getSelectedIcon();
				}
				else
				{
					return button->getDefaultIcon();
				}
			}

			void ButtonTheme::propertyChanged(const event::PropertyEvent &e)
			{
				if(e.getClassID() == event::PropertyEvent::SPECIAL)
				{
					int id = e.getID();

					AbstractButton *comp = static_cast<AbstractButton*>(e.getSource());

					util::Paint *foreground(comp->getForeground());
					util::Paint *background(comp->getBackground());

					switch(id)
					{
					case AbstractButton::SELECTED:
						{
							if(comp->isContentAreaFilled())
							{
								comp->setBackground(foreground);
								comp->setForeground(background);
							}
							break;
						}
					case AbstractButton::DESELECTED:
						{
							if(comp->isContentAreaFilled())
							{
								comp->setBackground(foreground);
								comp->setForeground(background);
							}
							break;
						}
					}
				}
			}

			const util::Dimension ButtonTheme::getPreferredSize(const Component *comp) const
			{
				const AbstractButton *button = static_cast<const AbstractButton*>(comp);

				util::Dimension ret(textUtil.getPreferredBoundingBox(button->getText(),getActiveIcon(button),button->getFont()));

				ret.width += button->getMargin().left + button->getMargin().right + button->getInsets().left + button->getInsets().right;
				ret.height+= button->getMargin().top + button->getMargin().bottom + button->getInsets().top + button->getInsets().bottom; 

				return ret;
			}
		}
	}
}