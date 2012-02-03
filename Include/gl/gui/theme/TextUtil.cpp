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
#include "./TextUtil.h"
#include "../Component.h"
#include "../Graphics.h"
#include "../Font.h"
#include "../Icon.h"

namespace ui
{
	namespace theme
	{
		void TextUtil::paintButton(int x, int y, Graphics &g, const StringInfoBuffer &buffer, int alignment, Icon *icon) const
		{

		}

		void TextUtil::paintButtonFocus(int x, int y, Graphics &g, const StringInfoBuffer &buffer, int spacing, Icon *icon) const
		{
			util::Dimension boundingBox(getBufferBoundingBox(buffer));
			
			if(icon != 0)
			{
				if(icon->getIconHeight() >= boundingBox.height)
				{
					boundingBox.width += icon->getIconWidth();
					boundingBox.height = icon->getIconHeight();
				}
				else
				{
					boundingBox.width += icon->getIconWidth();
				}
				g.drawRect(x - spacing, y - spacing, boundingBox.width + spacing + spacing, boundingBox.height + spacing + spacing);
			}
			else
			{
				g.drawRect(x - spacing, y - spacing, boundingBox.width + spacing + spacing, boundingBox.height + spacing + spacing);
			}
		}

		util::Dimension TextUtil::getContentBoundingBox(const util::Dimension &bufferBoundingBox, Icon *icon) const
		{
			util::Dimension ret(bufferBoundingBox);	
			if(icon != 0)
			{
				ret.width += icon->getIconWidth();
				ret.height = std::max(ret.height,icon->getIconHeight());
			}
			return ret;
		}

		util::Point TextUtil::getContentAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, const util::Dimension &contentBoundingBox) const
		{
			util::Point ret;
			
			switch(horizontalAlignment)
			{
				case Component::CENTER:
				{
					ret.x = insets.left + margin.left + (((boundingBox.width - insets.left - insets.right - margin.left - margin.right) /2) - (contentBoundingBox.width / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.x = insets.left + margin.left;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.x = (boundingBox.width - contentBoundingBox.width) - insets.right - margin.right;
					break;
				}
			}

			switch(verticalAlignment)
			{
				case AbstractButton::CENTER:
				{
					ret.y = insets.top + margin.top + (((boundingBox.height - insets.top - margin.top - insets.bottom - margin.bottom) / 2) - (contentBoundingBox.height / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.y = insets.top + margin.top;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.y = (boundingBox.height - contentBoundingBox.height) - insets.bottom - margin.bottom;
					break;
				}
			}
			return ret;
		}

		util::Point TextUtil::getIconAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, Icon *icon) const
		{
			util::Point ret;
			util::Dimension contentBoundingBox(icon->getIconWidth(),icon->getIconHeight());

			switch(horizontalAlignment)
			{
				case Component::CENTER:
				{
					ret.x = insets.left + margin.left + (((boundingBox.width - insets.left - insets.right - margin.left - margin.right) /2) - (contentBoundingBox.width / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.x = insets.left + margin.left;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.x = (boundingBox.width - contentBoundingBox.width) - insets.right - margin.right;
					break;
				}
			}

			switch(verticalAlignment)
			{
				case AbstractButton::CENTER:
				{
					ret.y = insets.top + margin.top + (((boundingBox.height - insets.top - margin.top - insets.bottom - margin.bottom) / 2) - (contentBoundingBox.height / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.y = insets.top + margin.top;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.y = (boundingBox.height - contentBoundingBox.height) - insets.bottom - margin.bottom;
					break;
				}
			}

			return ret;
		}

		util::Point TextUtil::getTextAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, const StringInfoBuffer &buffer) const
		{
			util::Dimension contentBoundingBox(getBufferBoundingBox(buffer));
			util::Point ret;
/*
			if(icon != 0)
			{
				contentBoundingBox.width += icon->getIconWidth();
				contentBoundingBox.height = std::max(contentBoundingBox.height,icon->getIconHeight());
			}
			*/

			switch(horizontalAlignment)
			{
				case Component::CENTER:
				{
					ret.x = insets.left + margin.left + (((boundingBox.width - insets.left - insets.right - margin.left - margin.right) /2) - (contentBoundingBox.width / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.x = insets.left + margin.left;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.x = (boundingBox.width - contentBoundingBox.width) - insets.right - margin.right;
					break;
				}
			}

			switch(verticalAlignment)
			{
				case AbstractButton::CENTER:
				{
					ret.y = insets.top + margin.top + (((boundingBox.height - insets.top - margin.top - insets.bottom - margin.bottom) / 2) - (contentBoundingBox.height / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					ret.y = insets.top + margin.top;
					break;
				}
				case AbstractButton::RIGHT:
				{
					ret.y = (boundingBox.height - contentBoundingBox.height) - insets.bottom - margin.bottom;
					break;
				}
			}
			return ret;
		}
		
		util::Dimension TextUtil::getBufferBoundingBox(const StringInfoBuffer &buffer) const
		{
			StringInfoBuffer::const_iterator iter;
			util::Dimension result;

			for(iter = buffer.begin(); iter != buffer.end(); ++iter)
			{
				result.width = std::max(result.width,(*iter).second.width);
				result.height += (*iter).second.height;
			}
			return result;
		}

		std::string TextUtil::getMaxString(const std::string &str, Font *font, int maxWidth) const
		{	
			//int width = 0;
			std::string::size_type index = 0;
		//	while(width <= maxWidth)
		//	{
		//		width = font->getStringBoundingBox(str.substr(0,index)).width;
		//		index++;
		//	}
			/*
			for(std::string::size_type index = 0; index < str.length(); ++index)
			{

			}
			*/
			if(index >= 6)
			{
				std::string result(str.substr(0,index - 6));
				return result.append("...");
			}
			return std::string("");
		}

		StringInfoBuffer TextUtil::getButtonString(Font *font, const std::string &text) const
		{
			StringInfoBuffer result;
			std::vector<std::string> tempString(splitText(text));
			std::vector<std::string>::const_iterator iter;

			for(iter = tempString.begin(); iter != tempString.end(); ++iter)
			{
				result.push_back(StringInfo((*iter),font->getStringBoundingBox((*iter))));
			}
			return result;
		}

		StringInfoBuffer TextUtil::getButtonString(const util::Dimension &boundingBox, const util::Insets &margin, Font *font, const std::string &text, bool wordWrap) const
		{
			StringInfoBuffer result;
			std::vector<std::string> tempString(splitText(text));
			std::vector<std::string>::const_iterator iter;

			int height = 0;
			for(iter = tempString.begin(); iter != tempString.end(); ++iter)
			{
				util::Dimension stringBoundingBox = font->getStringBoundingBox((*iter));
				if((height + stringBoundingBox.height) <= (boundingBox.height - margin.bottom - margin.top))
				{
					if(stringBoundingBox.width <= (boundingBox.width - margin.left - margin.right))
					{
						result.push_back(StringInfo((*iter),util::Dimension(stringBoundingBox.width,stringBoundingBox.height)));
					}
					else
					{
						if(wordWrap)
						{
							/*
							//std::vector<std::string> result;
							std::string::size_type index = 0;
			
							while(index != std::string::npos)
							{
								int width = 0;
								std::string::size_type lineBreak = 0;
								while(width <= boundingBox.width)
								{
									lineBreak = (*iter).find(' ');
									width = font->getStringBoundingBox((*iter).substr(index,lineBreak));

									if(lineBreak == std::string::npos)
									{
										break;
									}
								}

								result.push_back(text.substr(index,lineBreak));

								if(lineBreak != std::string::npos)
								{
									index = lineBreak + 1;
								}
								else
								{
									break;
								}
							}
							*/
						}
						else
						{
							result.push_back(StringInfo(getMaxString((*iter),font,boundingBox.width),util::Dimension(boundingBox.width,stringBoundingBox.height)));
						}
					}	
				}
				height += stringBoundingBox.height;
			}
			return result;
		}

		StringBuffer TextUtil::splitText(const std::string &text) const
		{
			StringBuffer result;
			std::string::size_type index = 0;
			
			while(index != std::string::npos)
			{
				std::string::size_type lineBreak = text.find('\n',index);

				if(lineBreak == index)
				{
					result.push_back(std::string(""));
				}
				else
				{
					result.push_back(text.substr(index,lineBreak-index));
				}

				if(lineBreak != std::string::npos)
				{
					index = lineBreak + 1;
				}
				else
				{
					break;
				}
			}
			return result;
		}
		// -------------------------------------------------------------------
		StringInfoBuffer CuttoffAlgorithm::wrapText(const std::string &text, Font *font, int width) const
		{
			StringInfoBuffer result;
			util::Dimension bbox;
			std::string::size_type index = 0;
			while(index <= text.length())
			{
				bbox = font->getStringBoundingBox(text.substr(0,index));
				if(bbox.width >= width)
				{
					break;
				}
				index++;
			}
			if(index > 3)
			{
				result.push_back(StringInfo(text.substr(0,index-3).append("..."),bbox));
			}
			else
			{
				result.push_back(StringInfo(std::string(""),util::Dimension(0,0)));
			}
			return result;
		}
		// -------------------------------------------------------------------
		TextUtil::TextUtil(TextWrappingAlgorithm *algorithm)
			:	textWrappingAlgorithm(algorithm)
		{
		}

		StringInfoBuffer TextUtil::fitStringInBoundingBox(const std::string &text, const util::Dimension &componentBoundingBox, const util::Dimension &iconBoundingBox, Font *font, const util::Insets &componentInsets, const util::Insets &componentMargins) const
		{
			StringInfoBuffer result;
			StringBuffer tempString(splitText(text));
			StringBuffer::const_iterator end(tempString.end());

			int height = 0;
			for(StringBuffer::const_iterator iter = tempString.begin(); iter != end; ++iter)
			{
				util::Dimension stringBoundingBox(font->getStringBoundingBox((*iter)));
			
				if((height + stringBoundingBox.height) <= (componentBoundingBox.height - componentMargins.bottom - componentMargins.top))
				{
					if(stringBoundingBox.width <= (componentBoundingBox.width - componentMargins.left - componentMargins.right - componentInsets.left - componentInsets.right - iconBoundingBox.width))
					{
						result.push_back(StringInfo((*iter),util::Dimension(stringBoundingBox.width,stringBoundingBox.height)));
					}
					else
					{
						StringInfoBuffer data(textWrappingAlgorithm->wrapText((*iter),font,componentBoundingBox.width - componentMargins.left - componentMargins.right - componentInsets.left - componentInsets.right - iconBoundingBox.width));
						std::copy(data.begin(),data.end(), std::back_inserter(result));
					}	
				}
				height += stringBoundingBox.height;
			}
			return result;
		}
		
		util::Dimension TextUtil::getStringBoundingBox(const StringInfoBuffer &str) const
		{
			StringInfoBuffer::const_iterator end(str.end());
			int width(0);
			int height(0);

			for(StringInfoBuffer::const_iterator iter = str.begin(); iter != end; ++iter)
			{
				width = std::max(width,(*iter).second.width);
				height += (*iter).second.height;
			}
			return util::Dimension(width,height);
		}
		
		util::Dimension TextUtil::getIconBoundingBox(Icon *icon) const
		{
			if(icon != 0)
			{
				return util::Dimension(icon->getIconWidth(),icon->getIconHeight());
			}
			else
			{
				return util::Dimension();
			}
		}
		
		int TextUtil::getVerticalAlignment(const util::Dimension &contentBoundingBox, const util::Dimension &componentBoundingBox, int alignment, const util::Insets &componentInsets, const util::Insets &componentMargins) const
		{
			int y(0);

			switch(alignment)
			{
				case AbstractButton::CENTER:
				{
					y = componentInsets.top + componentMargins.top + (((componentBoundingBox.height - componentInsets.top - componentMargins.top - componentInsets.bottom - componentMargins.bottom) / 2) - (contentBoundingBox.height / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					y = componentInsets.top + componentMargins.top;
					break;
				}
				case AbstractButton::RIGHT:
				{
					y = (componentBoundingBox.height - contentBoundingBox.height) - componentInsets.bottom - componentMargins.bottom;
					break;
				}
			}
			return y;
		}
		
		int TextUtil::getHorizontalAlignment(const util::Dimension &textBoundingBox, const util::Dimension &iconBoundingBox, const util::Dimension &componentBoundingBox, int alignment, const util::Insets &componentInsets, const util::Insets &componentMargins) const
		{
			int width(textBoundingBox.width + iconBoundingBox.width);
			int x(0);

			switch(alignment)
			{
				case Component::CENTER:
				{
					x = componentInsets.left + componentMargins.left + (((componentBoundingBox.width - componentInsets.left - componentInsets.right - componentMargins.left - componentMargins.right) /2) - (width / 2));
					break;
				}
				case AbstractButton::LEFT:
				{
					x = componentInsets.left + componentMargins.left;
					break;
				}
				case AbstractButton::RIGHT:
				{
					x = (componentBoundingBox.width - width) - componentInsets.right - componentMargins.right;
					break;
				}
			}
			return x;
		}

		util::Dimension TextUtil::getPreferredBoundingBox(const std::string &text, Icon *icon, Font *font) const
		{
			StringBuffer tempString(splitText(text));
			StringBuffer::const_iterator end(tempString.end());

			int width(0);
			int height(0);

			for(StringBuffer::const_iterator iter = tempString.begin(); iter != end; ++iter)
			{
				util::Dimension bbox(font->getStringBoundingBox(*iter));
				width = std::max(width,bbox.width);
				height += bbox.height;
			}

			if(icon != 0)
			{
				width += icon->getIconWidth();
				height = std::max(height,icon->getIconHeight());
			}

			return util::Dimension(width,height);
		}
	}
}