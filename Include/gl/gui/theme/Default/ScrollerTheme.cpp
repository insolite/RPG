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
#include "./ScrollerTheme.h"
#include "../../Component.h"
#include "../../component/Scroller.h"
#include "../../Graphics.h"
#include "../../event/MouseEvent.h"
#include <cmath>

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			ScrollerTheme::ScrollerTheme()
				:	raisedShadow(130,130,130),
					background(200,200,200),
					raisedHighlight(255,255,255),
					scrollerKnob(48,20),
					backgroundRaisedHorizontal(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_180),
					backgroundLoweredHorizontal(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0),
					backgroundRaisedVertical(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_90),
					backgroundLoweredVertical(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_270)
			{
			}

			ScrollerTheme::~ScrollerTheme()
			{
			}

			void ScrollerTheme::installTheme(Component *comp)
			{
				comp->addMouseListener(this);
				comp->setBackground(&background);
			}

			void ScrollerTheme::deinstallTheme(Component *comp)
			{
				comp->removeMouseListener(this);
			}

			const util::Dimension ScrollerTheme::getPreferredSize(const Component *comp) const
			{
				const Scroller * scroller = static_cast<const Scroller*>(comp);

				if(scroller->getOrientation() == Scroller::HORIZONTAL)
				{
					return util::Dimension(140,20);
				}
				else
				{
					return util::Dimension(20,140);
				}
			}

			void ScrollerTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);
			
				const Scroller * scroller = static_cast<const Scroller*>(comp);

				int percentage = scroller->getThumbSize();

				if(scroller->getOrientation() == Scroller::HORIZONTAL)
				{
					scrollerKnob.width = static_cast<int>((static_cast<float>(scroller->getBounds().width) / 100.0f) * percentage);
				}
				else
				{
					scrollerKnob.width = static_cast<int>((static_cast<float>(scroller->getBounds().height) / 100.0f) * percentage);
				}

				if(scrollerKnob.width < 10)
				{
					scrollerKnob.width = 10;
				}
				
				if(scroller->getOrientation() == Scroller::HORIZONTAL)
				{
				//	int width = scroller->getBounds().width;
					int height = 6;

				//	int x = 0;
					int y = scroller->getBounds().height/2 - height/2;

					// scale the value
					float tmp = ((float)(scroller->getValue() - scroller->getMinimum()) / (float)(scroller->getMaximum() - scroller->getMinimum()));
					int location = (int) (tmp * (scroller->getBounds().width - scrollerKnob.width));
/*
					if(scroller->isAdjusting())
					{
						g.setPaint(&background);
						g.fillRect(x,y,width,height);
					}

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-2,height);
*/
					y = scroller->getBounds().height/2 - scrollerKnob.height/2;

					paintKnob(g,location,y,scrollerKnob.width, scrollerKnob.height,scroller->isAdjusting(), scroller->getOrientation());

				}
				else
				{
					int width = 6;
				//	int height = scroller->getBounds().height;

					int x = scroller->getBounds().width /2 - width /2;
				//	int y = 0;

					float tmp = ((float)(scroller->getValue() - scroller->getMinimum()) / (float)(scroller->getMaximum() - scroller->getMinimum()));
					int location = (int) (tmp * (scroller->getBounds().height - scrollerKnob.width));

					/*
					if(scroller->isAdjusting())
					{
						g.setPaint(&background);
						g.fillRect(x,y,width,height);
					}

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-2,height);
					*/
					x = scroller->getBounds().width/2 - scrollerKnob.height/2;

					paintKnob(g,x,location,scrollerKnob.height,scrollerKnob.width,scroller->isAdjusting(), scroller->getOrientation());
				}
			}

			void ScrollerTheme::paintKnob(Graphics &g, int x, int y, int width, int height, bool dragging, int orientation) const
			{
				if(orientation == Scroller::HORIZONTAL)
				{
					if(dragging)
					{
						g.setPaint(&backgroundLoweredHorizontal);
						g.fillRect(x,y,width,height-1); // NFI why it needs this
					}
					else
					{
						g.setPaint(&backgroundRaisedHorizontal);
						g.fillRect(x,y,width,height-1);	
					}

					y += 1;

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height-1);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-1,height-1);
				}
				else
				{
					if(dragging)
					{
						g.setPaint(&backgroundLoweredVertical);
						g.fillRect(x,y,width,height-1); // NFI why it needs this
					}
					else
					{
						g.setPaint(&backgroundRaisedVertical);
						g.fillRect(x,y,width,height-1);	
					}

					y += 1;

					g.setPaint(&raisedShadow);
					g.drawRect(x,y,width-1,height-1);

					g.setPaint(&raisedHighlight);
					g.drawRect(x+1,y+1,width-1,height-1);
				}
			}

			void ScrollerTheme::mouseMotion(const event::MouseEvent &e)
			{
				Scroller * scroller = static_cast<Scroller*>(e.getSource());

				if(scroller->isAdjusting())
				{
					if(scroller->getOrientation() == Scroller::HORIZONTAL)
					{
						int x = e.getX() - scroller->getLocationOnScreen().x;
						float distance = static_cast<float>((static_cast<float>(x) / static_cast<float>(scroller->getBounds().width) * static_cast<float>(scroller->getMaximum()-scroller->getMinimum()) + static_cast<float>(scroller->getMinimum())));
						scroller->setValue(distance);
					}
					else
					{
						int y = e.getY() - scroller->getLocationOnScreen().y;
						float distance = static_cast<float>((static_cast<float>(y) / static_cast<float>(scroller->getBounds().height) * static_cast<float>(scroller->getMaximum()-scroller->getMinimum()) + static_cast<float>(scroller->getMinimum())));
						scroller->setValue(distance);
					}
				}
			}

			void ScrollerTheme::mousePressed(const event::MouseEvent &e)
			{
				Scroller * scroller = static_cast<Scroller*>(e.getSource());

				util::Point screen(scroller->getLocationOnScreen());

				if(scroller->getOrientation() == Scroller::HORIZONTAL)
				{
					float tmp = ((float)(scroller->getValue() - scroller->getMinimum()) / (float)(scroller->getMaximum() - scroller->getMinimum()));
					int location = (int) (tmp * (scroller->getBounds().width - scrollerKnob.width));

					int y = scroller->getBounds().height/2 - scrollerKnob.height/2 + screen.y;
					int x = location + screen.x;
					util::Rectangle selectionKnob(x,y,scrollerKnob.width, scrollerKnob.height);

					if(selectionKnob.contains(e.getX(),e.getY()))
					{
						scroller->setAdjusting(true);
					}
					else
					{
						// jump to that position
						int x = e.getX() - scroller->getLocationOnScreen().x;
						float distance = static_cast<float>((static_cast<float>(x) / static_cast<float>(scroller->getBounds().width) * static_cast<float>(scroller->getMaximum()-scroller->getMinimum()) + static_cast<float>(scroller->getMinimum())));
						scroller->setValue(distance);
					}
				}
				else
				{
					float tmp = ((float)(scroller->getValue() - scroller->getMinimum()) / (float)(scroller->getMaximum() - scroller->getMinimum()));
					int location = (int) (tmp * (scroller->getBounds().height - scrollerKnob.width));

					int x = scroller->getBounds().width/2 - scrollerKnob.height/2 + screen.x;
					int y = location + screen.y;
					util::Rectangle selectionKnob(x,y,scrollerKnob.height,scrollerKnob.width);

					if(selectionKnob.contains(e.getX(),e.getY()))
					{
						scroller->setAdjusting(true);
					}
					else
					{
						// jump to that position
						int y = e.getY() - scroller->getLocationOnScreen().y;
						float distance = static_cast<float>((static_cast<float>(y) / static_cast<float>(scroller->getBounds().height) * static_cast<float>(scroller->getMaximum()-scroller->getMinimum()) + static_cast<float>(scroller->getMinimum())));
						scroller->setValue(distance);
					}
				}
			}

			void ScrollerTheme::mouseReleased(const event::MouseEvent &e)
			{
				Scroller * scroller = static_cast<Scroller*>(e.getSource());

				scroller->setAdjusting(false);
			}
		}
	}
}