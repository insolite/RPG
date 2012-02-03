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
#include "../../Component.h"
#include "../../component/Slider.h"
#include "../../Graphics.h"
#include "../../event/MouseEvent.h"
#include <cmath>

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			SliderTheme::SliderTheme()
				:	raisedShadow(130,130,130),
					background(200,200,200),
					raisedHighlight(255,255,255),
					sliderKnob(8,16),
					backgroundRaised(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_180),
					backgroundLowered(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0)
			{
			}

			SliderTheme::~SliderTheme()
			{
			}

			void SliderTheme::installTheme(Component *comp)
			{
				comp->addMouseListener(this);
			}

			void SliderTheme::deinstallTheme(Component *comp)
			{
				comp->removeMouseListener(this);
			}

			const util::Dimension SliderTheme::getPreferredSize(const Component *comp) const
			{
				const Slider * slider = static_cast<const Slider*>(comp);

				if(slider->getOrientation() == Component::HORIZONTAL)
				{
					return util::Dimension(140,20);
				}
				else
				{
					return util::Dimension(20,140);
				}
			}

			void SliderTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);
			
				const Slider * slider = static_cast<const Slider*>(comp);
				
				if(slider->getOrientation() == Component::HORIZONTAL)
				{
					int width = slider->getBounds().width;
					int height = 6;

					int x = 0;
					int y = slider->getBounds().height/2 - height/2;

					// scale the value
					float tmp = ((float)(slider->getValue() - slider->getMinimum()) / (float)(slider->getMaximum() - slider->getMinimum()));
					int location = (int) (tmp * (slider->getBounds().width - sliderKnob.width));

					if(slider->isAdjusting())
					{
						g.setPaint(&background);
						g.fillRect(x,y,width,height);
					}

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-2,height);

					y = slider->getBounds().height/2 - sliderKnob.height/2;

					paintKnob(g,location,y,sliderKnob.width, sliderKnob.height,slider->isAdjusting());

				}
				else
				{
					int width = 6;
					int height = slider->getBounds().height;

					int x = slider->getBounds().width /2 - width /2;
					int y = 0;

					float tmp = ((float)(slider->getValue() - slider->getMinimum()) / (float)(slider->getMaximum() - slider->getMinimum()));
					int location = (int) (tmp * (slider->getBounds().height - sliderKnob.width));

					if(slider->isAdjusting())
					{
						g.setPaint(&background);
						g.fillRect(x,y,width,height);
					}

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-2,height);

					x = slider->getBounds().width/2 - sliderKnob.height/2;

					paintKnob(g,x,location,sliderKnob.height,sliderKnob.width,slider->isAdjusting());
				}
			}

			void SliderTheme::paintKnob(Graphics &g, int x, int y, int width, int height, bool dragging) const
			{
				if(dragging)
				{
					g.setPaint(&backgroundLowered);
					g.fillRect(x,y,width,height-1); // NFI why it needs this
				}
				else
				{
					g.setPaint(&backgroundRaised);
					g.fillRect(x,y,width,height-1);	
				}

				g.setPaint(&raisedShadow);
				g.drawRect(x,y,width-1,height-1);

				g.setPaint(&raisedHighlight);
				g.drawRect(x+1,y+1,width-1,height-1);
			}

			void SliderTheme::mouseMotion(const event::MouseEvent &e)
			{
				Slider * slider = static_cast<Slider*>(e.getSource());

				if(slider->isAdjusting())
				{
					if(slider->getOrientation() == Component::HORIZONTAL)
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

			void SliderTheme::mousePressed(const event::MouseEvent &e)
			{
				Slider * slider = static_cast<Slider*>(e.getSource());

				util::Point screen(slider->getLocationOnScreen());

				if(slider->getOrientation() == Component::HORIZONTAL)
				{
					float tmp = ((float)(slider->getValue() - slider->getMinimum()) / (float)(slider->getMaximum() - slider->getMinimum()));
					int location = (int) (tmp * (slider->getBounds().width - sliderKnob.width));

					int y = slider->getBounds().height/2 - sliderKnob.height/2 + screen.y;
					int x = location + screen.x;
					util::Rectangle selectionKnob(x,y,sliderKnob.width, sliderKnob.height);

					if(selectionKnob.contains(e.getX(),e.getY()))
					{
						slider->setAdjusting(true);
					}
					else
					{
						// jump to that position
						int x = e.getX() - slider->getLocationOnScreen().x;
						float distance = static_cast<float>((static_cast<float>(x) / static_cast<float>(slider->getBounds().width) * static_cast<float>(slider->getMaximum()-slider->getMinimum()) + static_cast<float>(slider->getMinimum())));
						slider->setValue(distance);
					}
				}
				else
				{
					float tmp = ((float)(slider->getValue() - slider->getMinimum()) / (float)(slider->getMaximum() - slider->getMinimum()));
					int location = (int) (tmp * (slider->getBounds().height - sliderKnob.width));

					int x = slider->getBounds().width/2 - sliderKnob.height/2 + screen.x;
					int y = location + screen.y;
					util::Rectangle selectionKnob(x,y,sliderKnob.height,sliderKnob.width);

					if(selectionKnob.contains(e.getX(),e.getY()))
					{
						slider->setAdjusting(true);
					}
					else
					{
						// jump to that position
						int y = e.getY() - slider->getLocationOnScreen().y;
						float distance = static_cast<float>((static_cast<float>(y) / static_cast<float>(slider->getBounds().height) * static_cast<float>(slider->getMaximum()-slider->getMinimum()) + static_cast<float>(slider->getMinimum())));
						slider->setValue(distance);
					}
				}
			}

			void SliderTheme::mouseReleased(const event::MouseEvent &e)
			{
				Slider * slider = static_cast<Slider*>(e.getSource());

				slider->setAdjusting(false);
			}
		}
	}
}