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
#include "./SliderTheme.h"
#include "../../component/Slider.h"
#include "../../Graphics.h"

namespace ui
{
	namespace theme
	{
		namespace basic
		{
			SliderTheme::SliderTheme()
				:	black(0,0,0),
					white(255,255,255)
			{
			}

			SliderTheme::~SliderTheme()
			{
			}

			const util::Dimension SliderTheme::getPreferredSize(const Component *comp) const
			{
				const Slider * slider = static_cast<const Slider *>(comp);
				return rangeUtil.getPreferredSize(slider->getOrientation());
			}

			void SliderTheme::installTheme(Component *comp)
			{
				comp->setBackground(&black);
				comp->addMouseListener(this);
			}

			void SliderTheme::deinstallTheme(Component *comp)
			{
				comp->removeMouseListener(this);
			}

			void SliderTheme::paint(Graphics &g, const Component *comp) const
			{
				BasicComponent::paint(g,comp);

				const Slider * slider = static_cast<const Slider *>(comp);


				g.setPaint(&white);
				util::Rectangle rec = comp->getBounds();
				if(slider->getOrientation() == Component::HORIZONTAL)
				{
					int height = 5;

					g.drawRect(slider->getInsets().left,slider->getInsets().top + (rec.height / 2) - (height / 2) ,rec.width - slider->getInsets().right, height - slider->getInsets().bottom);
				}
				else
				{
					int width = 5;
					g.drawRect(slider->getInsets().left + (rec.width / 2) - (width /2), slider->getInsets().top,width - slider->getInsets().right, rec.height - slider->getInsets().bottom);
				}
			}

			void SliderTheme::mousePressed(const event::MouseEvent &e)
			{
			}

			void SliderTheme::mouseReleased(const event::MouseEvent &e)
			{
			}

			void SliderTheme::mouseMotion(const event::MouseEvent &e)
			{
				Slider *slider = static_cast<Slider*>(e.getSource());
				if(slider->isAdjusting())
				{
					int x = e.getX() - slider->getLocationOnScreen().x;
					float distance = static_cast<float>((static_cast<float>(x) / static_cast<float>(slider->getBounds().width) * static_cast<float>(slider->getMaximum()-slider->getMinimum()) + static_cast<float>(slider->getMinimum())));
					slider->setValue(distance);
				}
				else
				{
					int y = e.getY() - slider->getLocationOnScreen().y;
					float distance = static_cast<float>((static_cast<float>(y) / static_cast<float>(slider->getBounds().height) * static_cast<float>(slider->getMaximum()-slider->getMinimum()) + static_cast<float>(slider->getMinimum())));
					slider->setValue(distance);
				}
			}
		}
	}
}