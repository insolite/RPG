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
#include "./LabelTheme.h"
#include "../../Component.h"
#include "../../Graphics.h"
#include "../../Font.h"
#include "../../GlyphContext.h"

namespace ui
{
	namespace theme
	{
		namespace basic
		{
			LabelTheme::LabelTheme()
				:
					textUtil(&algorithm)
			{
			}

			void LabelTheme::installTheme(Component *comp)
			{
				Label *label = static_cast<Label*>(comp);
				
				label->setMargin(util::Insets(10,10,10,10));
				label->setFont(GlyphContext::getInstance().createFont("Vera.ttf",10));
			}

			void LabelTheme::deinstallTheme(Component *comp)
			{
			}

			void LabelTheme::paint(Graphics &g, const Component *comp) const
			{
				BasicComponent::paint(g,comp);

				const Label *label = static_cast<const Label*>(comp);

				util::Dimension componentBoundingBox(label->getBounds().width,label->getBounds().height);
				util::Dimension iconBoundingBox(textUtil.getIconBoundingBox(getActiveIcon(label)));

				StringInfoBuffer stringInfo(textUtil.fitStringInBoundingBox(label->getText(),componentBoundingBox,iconBoundingBox,label->getFont(),label->getInsets(),label->getMargin()));

				util::Dimension stringBoundingBox(textUtil.getStringBoundingBox(stringInfo));

				int verticalIconAlignment = textUtil.getVerticalAlignment(iconBoundingBox,componentBoundingBox,label->getVerticalAlignment(),label->getInsets(),label->getMargin());
				int verticalTextAlignment = textUtil.getVerticalAlignment(stringBoundingBox,componentBoundingBox,label->getVerticalAlignment(),label->getInsets(),label->getMargin());
				int horizontalAlignment = textUtil.getHorizontalAlignment(stringBoundingBox,iconBoundingBox,componentBoundingBox,label->getHorizontalAlignment(),label->getInsets(),label->getMargin());

				if(getActiveIcon(label) != 0)
				{
					getActiveIcon(label)->paint(label,g,horizontalAlignment,verticalIconAlignment);
					horizontalAlignment += getActiveIcon(label)->getIconWidth();
				}

				g.setPaint(label->getForeground());
				g.setFont(label->getFont());

				if(getActiveIcon(label) != 0)
				{
					paintLabel(horizontalAlignment,verticalTextAlignment,g,stringInfo,stringBoundingBox,Component::LEFT,getActiveIcon(label));
				}
				else
				{
					paintLabel(horizontalAlignment,verticalTextAlignment,g,stringInfo,stringBoundingBox,Component::CENTER,getActiveIcon(label));
				}
			}

			void LabelTheme::paintLabel(int x, int y, Graphics &g, const StringInfoBuffer &buffer, const util::Dimension &stringBoundingBox ,int alignment, Icon *icon) const
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

			const util::Dimension LabelTheme::getPreferredSize(const Component *comp) const
			{
				const Label *label = static_cast<const Label*>(comp);

				util::Dimension ret(textUtil.getPreferredBoundingBox(label->getText(),getActiveIcon(label),label->getFont()));

				ret.width += label->getMargin().left + label->getMargin().right + label->getInsets().left + label->getInsets().right;
				ret.height+= label->getMargin().top + label->getMargin().bottom + label->getInsets().top + label->getInsets().bottom; 

				return ret;
			}

			Icon * LabelTheme::getActiveIcon(const Label *label) const
			{
				return label->getIcon();
			}
		}
	}
}