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
#include "./Util.h"
#include "../../util/Dimension.h"
#include "../../Font.h"
#include "../../Graphics.h"
#include "../../Icon.h"
#include "./Scheme.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			std::string Util::getButtonString(const AbstractButton *button)
			{
				// this function might appear quite slow, and in fact, it is.
				// the speed depends on the font engine implementation, having
				// a fast font engine, with for example cached glyph dimensions speeds
				// up the whole font rendering.
				util::Dimension bbox(button->getFont()->getStringBoundingBox(button->getText()));
			//	int width = bbox.width;
			//	int height = bbox.height;

				if((bbox.height <= button->getBounds().height - button->getMargin().bottom - button->getMargin().top))
				{
					if((bbox.width <= button->getBounds().width - button->getMargin().left - button->getMargin().right))
					{
						// it fits, no questions asked
						return button->getText();
					}
					else
					{
						// by now, the text does not fit in our Component,
						// let's see if chopping off some characters helps.
						std::string text = button->getText();
						std::string final;
						for(std::size_t i = 0; i < text.length(); ++i)
						{
							std::string tmp(final);
							util::Dimension strbbox(button->getFont()->getStringBoundingBox(tmp.append(".......")));
							if(strbbox.width < (button->getBounds().width - button->getMargin().left - button->getMargin().right) && strbbox.height < button->getBounds().height)
							{
								// so far we fit, append one char and try again
								//std::string(text[i]);
								final += text[i];
							}
							else
							{
								if(final != "")
								{
									final.append("...");
								}
								break;
							}
						}
						return final;
					}
				}
				return "";
			}

			const util::Dimension Util::getButtonSize(const AbstractButton *button)
			{
				std::string text = button->getText();
				Font *f = button->getFont();

				util::Dimension bbox(f->getStringBoundingBox(text));
				int width = bbox.width + button->getMargin().left + button->getMargin().right + button->getInsets().left + button->getInsets().right;
				int height= bbox.height + button->getMargin().top + button->getMargin().bottom + button->getInsets().top + button->getInsets().bottom; 	

				if(getActiveIcon(button) != 0)
				{
					width += getActiveIcon(button)->getIconWidth();
					height = std::max(height,button->getMargin().top + button->getMargin().bottom + button->getInsets().top + button->getInsets().bottom + getActiveIcon(button)->getIconHeight());
				}

				util::Dimension preferredSize(width,height);

				return preferredSize;
			}



			Icon * Util::getActiveIcon(const AbstractButton *button)
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

			void Util::paintMenuItem(const MenuItem *button, Graphics &g)
			{
				// this is slow due to the Font engine not caching these values,
				// but instead calculating them on the fly. Performance could
				// be improved by writing a better font engine.
				// HACK HACK: edited the font engine to cache values :|
				//std::string str = Util::getButtonString(button);
				std::string str = button->getText();
				util::Dimension rec(button->getFont()->getStringBoundingBox(str));
				util::Point alignment(Util::getButtonAlignment(button,str,rec));

				
				if(button->isFocusPainted() && button->hasFocus())
				{
					// HACK HACK: since the font engine does not properly calculate the
					// string bounding box, we add some random value to the boundingbox.
					// Sigh.
					//int offset = 3;
					//util::Color focus(139,178,206);
					g.setPaint(SchemeManager::getInstance().getScheme()->getHighlight());
					g.fillRect(0,0,button->getBounds().width,button->getBounds().height);
					//g.drawRect(alignment.x - offset,alignment.y - offset,rec.width + offset + offset,rec.height + offset + offset);
				}

			

					
				g.setPaint(button->getForeground());
				g.setFont(button->getFont());
				g.drawString(alignment.x,alignment.y,str);
			
				paintIcon(button,g,str);

			}

			void Util::paintButton(const AbstractButton *button, Graphics &g)
			{			
				// this is slow due to the Font engine not caching these values,
				// but instead calculating them on the fly. Performance could
				// be improved by writing a better font engine.
				// HACK HACK: edited the font engine to cache values :|
				std::string str = Util::getButtonString(button);
				util::Dimension rec(button->getFont()->getStringBoundingBox(str));
				util::Point alignment(Util::getButtonAlignment(button,str,rec));

				
				if(button->isFocusPainted() && button->hasFocus())
				{
					// HACK HACK: since the font engine does not properly calculate the
					// string bounding box, we add some random value to the boundingbox.
					// Sigh.
					int offset = 3;
					//util::Color focus(139,178,206);
					g.setPaint(SchemeManager::getInstance().getScheme()->getHighlight());
					g.drawRect(alignment.x - offset,alignment.y - offset,rec.width + offset + offset,rec.height + offset + offset);
				}

				// beware that this goes out of scope at the end of the function.
				util::LighterPaint lighter(button->getForeground());

				if(!button->isEnabled())
				{	
					g.setPaint(&lighter);
				}
				else
				{
					g.setPaint(button->getForeground());	
				}
				g.setFont(button->getFont());
				g.drawString(alignment.x,alignment.y,str);
			
				paintIcon(button,g,str);
				
			}

			void Util::paintIcon(const AbstractButton *button, Graphics &g, const std::string &text)
			{
				if(getActiveIcon(button) != 0)
				{
				
					util::Dimension comp(button->getBounds().width,button->getBounds().height);

					if((comp.height < getActiveIcon(button)->getIconHeight()) || (comp.width < getActiveIcon(button)->getIconWidth()))
					{
						return;
					}

					int x = 0;
					int y = 0;


					
					int horizontalAlignment = button->getHorizontalAlignment();

					switch(horizontalAlignment)
					{
					case AbstractButton::CENTER:
						{
							util::Dimension bbox(button->getFont()->getStringBoundingBox(text));
							x = (comp.width / 2) - (bbox.width / 2) - (getActiveIcon(button)->getIconWidth() /2);/*/2 - getActiveIcon(button)->getIconWidth()/2;*/
							break;
						}
					case AbstractButton::LEFT:
						{
							x = button->getMargin().left;
							break;
						}
					case AbstractButton::RIGHT:
						{
							x = comp.width - button->getMargin().right - getActiveIcon(button)->getIconWidth();
							break;
						}
					}

					
					int verticalAlignment = button->getVerticalAlignment();

					switch(verticalAlignment)
					{
					case AbstractButton::CENTER:
						{
							y = button->getBounds().height/2 - getActiveIcon(button)->getIconHeight()/2;
							break;
						}
					case AbstractButton::LEFT:
						{
							y = button->getMargin().top;
							break;
						}
					case AbstractButton::RIGHT:
						{
							y = button->getMargin().bottom;
							break;
						}
					}

					getActiveIcon(button)->paint(button,g,x,y);		
				}	
			}

			util::Point Util::getButtonAlignment(const AbstractButton *button, const std::string &text, const util::Dimension &bbox)
			{
				util::Point ret;
				//util::Dimension bbox(button->getFont()->getStringBoundingBox(text));
				util::Dimension comp(button->getBounds().width,button->getBounds().height);

				int horizontalAlignment = button->getHorizontalAlignment();

				switch(horizontalAlignment)
				{
				case AbstractButton::CENTER:
					{
						if(getActiveIcon(button) != 0)
						{
							ret.x = (comp.width / 2) - (bbox.width / 2) + (getActiveIcon(button)->getIconWidth() / 2);
						}
						else
						{
							ret.x = (comp.width / 2) - (bbox.width / 2);
						}
						break;
					}
				case AbstractButton::LEFT:
					{
						if(getActiveIcon(button) != 0)
						{
							ret.x = button->getMargin().left + getActiveIcon(button)->getIconWidth();
						}
						else
						{
							ret.x = button->getMargin().left;
						}
						break;
					}
				case AbstractButton::RIGHT:
					{
						if(getActiveIcon(button) != 0)
						{
							ret.x = comp.width - button->getMargin().right - bbox.width - getActiveIcon(button)->getIconWidth();
						}
						else
						{
							ret.x = comp.width - button->getMargin().right - bbox.width;
						}
						break;
					}
				}

				int verticalAlignment = button->getVerticalAlignment();

				switch(verticalAlignment)
				{
				case AbstractButton::CENTER:
					{
						ret.y = (comp.height / 2) - (bbox.height / 2);
						break;
					}
				case AbstractButton::LEFT:
					{
						ret.y = button->getMargin().top;
						break;
					}
				case AbstractButton::RIGHT:
					{
						ret.y = button->getMargin().bottom;
						break;
					}
				}
				return ret;
			}
		}
	}
}