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
#include "./Util.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			LabelTheme::LabelTheme()
				:	foreground(0,0,0)
			{
			}

			void LabelTheme::installTheme(Component *comp)
			{
				Label *label = static_cast<Label*>(comp);
				
				//label->setForeground(&foreground);
				label->setBorderPainted(true);
				label->setMargin(util::Insets(7,7,7,7));
				label->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void LabelTheme::deinstallTheme(Component *comp)
			{
			}

			void LabelTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const Label *label = static_cast<const Label*>(comp);

				paintLabel(label,g);

			}

			const util::Dimension LabelTheme::getPreferredSize(const Component *comp) const
			{
				const Label *label = static_cast<const Label*>(comp);

				return getLabelSize(label);
			}

			std::string LabelTheme::getLabelString(const Label *label) const
			{
				// this function might appear quite slow, and in fact, it is.
				// the speed depends on the font engine implementation, having
				// a fast font engine, with for example cached glyph dimensions speeds
				// up the whole font rendering.
				util::Dimension bbox(label->getFont()->getStringBoundingBox(label->getText()));
			//	int width = bbox.width;
			//	int height = bbox.height;

				if((bbox.height <= label->getBounds().height - label->getMargin().bottom - label->getMargin().top))
				{
					if((bbox.width <= label->getBounds().width - label->getMargin().left - label->getMargin().right))
					{
						// it fits, no questions asked
						return label->getText();
					}
					else
					{
						// by now, the text does not fit in our Component,
						// let's see if chopping off some characters helps.
						std::string text = label->getText();
						std::string final;
						for(std::size_t i = 0; i < text.length(); ++i)
						{
							std::string tmp(final);
							util::Dimension strbbox(label->getFont()->getStringBoundingBox(tmp.append(".......")));
							if(strbbox.width < (label->getBounds().width - label->getMargin().left - label->getMargin().right) && strbbox.height < label->getBounds().height)
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

			const util::Dimension LabelTheme::getLabelSize(const Label *label) const
			{
				std::string text = label->getText();
				Font *f = label->getFont();

				util::Dimension bbox(f->getStringBoundingBox(text));
				int width = bbox.width + label->getMargin().left + label->getMargin().right + label->getInsets().left + label->getInsets().right;
				int height= bbox.height + label->getMargin().top + label->getMargin().bottom + label->getInsets().top + label->getInsets().bottom; 	

				if(getActiveIcon(label) != 0)
				{
					width += getActiveIcon(label)->getIconWidth();
					height = std::max(height,label->getMargin().top + label->getMargin().bottom + label->getInsets().top + label->getInsets().bottom + getActiveIcon(label)->getIconHeight());
				}

				util::Dimension preferredSize(width,height);

				return preferredSize;
			}

			Icon * LabelTheme::getActiveIcon(const Label *label) const
			{
				return label->getIcon();
			}

			void LabelTheme::paintLabel(const Label *label, Graphics &g) const
			{			
				// this is slow due to the Font engine not caching these values,
				// but instead calculating them on the fly. Performance could
				// be improved by writing a better font engine.
				// HACK HACK: edited the font engine to cache values :|
				std::string str = getLabelString(label);
				util::Point alignment(getLabelAlignment(label,str));

				util::Dimension rec(label->getFont()->getStringBoundingBox(str));
			
				g.setPaint(label->getForeground());
				g.setFont(label->getFont());
				g.drawString(alignment.x,alignment.y,str);
			
				paintIcon(label,g,str);
				
			}

			void LabelTheme::paintIcon(const Label *label, Graphics &g, const std::string &text) const
			{
				if(getActiveIcon(label) != 0)
				{
				
					util::Dimension comp(label->getBounds().width,label->getBounds().height);

					int x = 0;
					int y = 0;


					
					int horizontalAlignment = label->getHorizontalAlignment();

					switch(horizontalAlignment)
					{
					case AbstractButton::CENTER:
						{
							util::Dimension bbox(label->getFont()->getStringBoundingBox(text));
							x = (comp.width / 2) - (bbox.width / 2) - (getActiveIcon(label)->getIconWidth() /2);/*/2 - getActiveIcon(button)->getIconWidth()/2;*/
							break;
						}
					case AbstractButton::LEFT:
						{
							x = label->getMargin().left;
							break;
						}
					case AbstractButton::RIGHT:
						{
							x = comp.width - label->getMargin().right - getActiveIcon(label)->getIconWidth();
							break;
						}
					}

					
					int verticalAlignment = label->getVerticalAlignment();

					switch(verticalAlignment)
					{
					case AbstractButton::CENTER:
						{
							y = label->getBounds().height/2 - getActiveIcon(label)->getIconHeight()/2;
							break;
						}
					case AbstractButton::LEFT:
						{
							y = label->getMargin().top;
							break;
						}
					case AbstractButton::RIGHT:
						{
							y = label->getMargin().bottom;
							break;
						}
					}

					getActiveIcon(label)->paint(label,g,x,y);		
				}	
			}


			util::Point LabelTheme::getLabelAlignment(const Label *label, const std::string &text) const
			{
				util::Point ret;
				util::Dimension bbox(label->getFont()->getStringBoundingBox(text));
				util::Dimension comp(label->getBounds().width,label->getBounds().height);

				int horizontalAlignment = label->getHorizontalAlignment();

				switch(horizontalAlignment)
				{
				case AbstractButton::CENTER:
					{
						if(getActiveIcon(label) != 0)
						{
							ret.x = (comp.width / 2) - (bbox.width / 2) + (getActiveIcon(label)->getIconWidth() / 2);
						}
						else
						{
							ret.x = (comp.width / 2) - (bbox.width / 2);
						}
						break;
					}
				case AbstractButton::LEFT:
					{
						if(getActiveIcon(label) != 0)
						{
							ret.x = label->getMargin().left + getActiveIcon(label)->getIconWidth();
						}
						else
						{
							ret.x = label->getMargin().left;
						}
						break;
					}
				case AbstractButton::RIGHT:
					{
						if(getActiveIcon(label) != 0)
						{
							ret.x = comp.width - label->getMargin().right - bbox.width - getActiveIcon(label)->getIconWidth();
						}
						else
						{
							ret.x = comp.width - label->getMargin().right - bbox.width;
						}
						break;
					}
				}

				int verticalAlignment = label->getVerticalAlignment();

				switch(verticalAlignment)
				{
				case AbstractButton::CENTER:
					{
						ret.y = (comp.height / 2) - (bbox.height / 2);
						break;
					}
				case AbstractButton::LEFT:
					{
						ret.y = label->getMargin().top;
						break;
					}
				case AbstractButton::RIGHT:
					{
						ret.y = label->getMargin().bottom;
						break;
					}
				}
				return ret;
			}


		}
	}
}