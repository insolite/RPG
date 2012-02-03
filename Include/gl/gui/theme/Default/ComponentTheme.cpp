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
#include "./ComponentTheme.h"
#include "../../Component.h"
#include "../../Graphics.h"
#include "../../SelectionManager.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			ComponentTheme::ComponentTheme()
				:	defaultBackground(224,224,224),
					defaultForeground(0,0,0)
			{

			}

			ComponentTheme::~ComponentTheme()
			{
			}

			void ComponentTheme::paint(Graphics &g, const Component *comp) const
			{
				// default behaviour
				g.setPaint(comp->getBackground());
		
				int width = comp->getBounds().width - comp->getInsets().left - comp->getInsets().right;
				int height = comp->getBounds().height - comp->getInsets().bottom - comp->getInsets().top;

				g.fillRect(comp->getInsets().left,comp->getInsets().top,width,height);

			}

			void ComponentTheme::paintSelection(Graphics &g, const Component *comp) const
			{
				int index = SelectionManager::getInstance().getComponentId(comp);

				int width = comp->getBounds().width;
				int height = comp->getBounds().height;

				g.paintUniqueColoredRect(index,0,0,width,height);
			}

			void ComponentTheme::installTheme(Component *comp)
			{
				comp->setBackground(SchemeManager::getInstance().getScheme()->getDefaultBackground());
				comp->setForeground(SchemeManager::getInstance().getScheme()->getTextColor());
				comp->setBorderPainted(true);
			}

			void ComponentTheme::deinstallTheme(Component *comp)
			{
			}

			const util::Dimension ComponentTheme::getPreferredSize(const Component *comp) const
			{
				return util::Dimension(-1,-1);
			}
		}
	}
}