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
#include "./FlowLayout.h"
#include "../Container.h"
#include "../util/Rectangle.h"
#include "../util/Dimension.h"
#include "../util/Insets.h"

namespace ui
{
	namespace layout
	{
		FlowLayout::FlowLayout()
			:	alignment(Component::CENTER)
		{
			setHgap(5);
			setVgap(5);
		}

		FlowLayout::FlowLayout(const FlowLayout& rhs)
			:	LayoutManager(static_cast<LayoutManager>(rhs)),
				alignment(rhs.alignment)
		{
		}

		FlowLayout& FlowLayout::operator =(const FlowLayout& rhs)
		{
			FlowLayout temp(rhs);
			swap(temp);
			return *this;
		}

		void FlowLayout::swap(FlowLayout& rhs) throw()
		{
			std::swap(alignment,rhs.alignment);
		}

		FlowLayout::FlowLayout(int align)
			:	alignment(align)
		{
			setHgap(5);
			setVgap(5);
		}

		FlowLayout::FlowLayout(int align, int hgap, int vgap)
			:	alignment(align)
		{
			setHgap(hgap);
			setVgap(vgap);
		}

		const util::Dimension FlowLayout::preferredLayoutSize(const Container* parent) const
		{
			util::Dimension preferredSize;

			ComponentList::const_iterator iter;
			ComponentList list = parent->getChildren();

			bool firstComponent = false;

			for(iter = list.begin(); iter != list.end(); ++iter)
			{
				if((*iter)->isVisible())
				{
					preferredSize.height = std::max(preferredSize.height,(*iter)->getPreferredSize().height);
					preferredSize.width += (*iter)->getPreferredSize().width;

					if(firstComponent)
					{
						firstComponent = false;
					}
					else
					{
						preferredSize.width += getHgap();
					}
				}
			}
			
			util::Insets parentInsets = parent->getInsets();

			preferredSize.width += parentInsets.left + parentInsets.right + getHgap() + getHgap();
			preferredSize.height += parentInsets.top + parentInsets.bottom + getVgap() + getVgap();

			return preferredSize;
			/*
			util::Dimension dim;
			dim.height = 0;
			dim.width = 0;

			bool first = true;

			ComponentList::iterator iter;
			ComponentList childList = parent->getChildren();
			for(iter = childList.begin(); iter != childList.end(); ++iter)
			{
				if((*iter)->isVisible())
				{
 					dim.height = std::max(dim.height,(*iter)->getPreferredSize().height);

					if(first)
						first = false;
					else
						dim.width += getHgap();

					dim.width += (*iter)->getPreferredSize().width;
				}
			}

			dim.width += parent->getInsets().left + parent->getInsets().right + getHgap() * 2;
			dim.height += parent->getInsets().top + parent->getInsets().bottom + getVgap() * 2;

			return dim;
			*/
		}

		void FlowLayout::layoutContainer(const Container* parent)
		{			/*
			util::Insets insets = parent->getInsets();

			int maxWidth = parent->getBounds().width - (insets.left + insets.right + getHgap()*2);
			int numComponents = parent->getNumberOfChildren();
			int x = 0;
			int y = insets.top + getVgap();

			int rowHeight = 0, start = 0;

			ComponentList::iterator iter;
			ComponentList list = parent->getChildren();
			int i = 0;
			for(iter = list.begin(); iter != list.end(); ++iter)
			{
				Component* comp = (*iter);
				if(comp->isVisible())
				{
					comp->setSize(comp->getPreferredSize().width,comp->getPreferredSize().height);

					if((x == 0) || ((x + comp->getPreferredSize().width) <= maxWidth))
					{
						if(x > 0)
						{
							x += getHgap();
						}
						x += comp->getPreferredSize().width;
						rowHeight = std::max(rowHeight,comp->getPreferredSize().height);
					}
					else
					{
						moveComponents(parent,insets.left + getHgap(),y,maxWidth -x, rowHeight, start, i);

						x = comp->getPreferredSize().width;
						y += getVgap() + rowHeight;
						rowHeight = comp->getPreferredSize().height;
						start = i;
					}
				}
				++i;
			}
			moveComponents(parent,insets.left + getHgap(),y,maxWidth -x, rowHeight, start, numComponents);
			*/

			
			util::Dimension rowDimension(0,0);
			util::Insets parentInsets = parent->getInsets();
			util::Dimension parentDimension(parent->getBounds().width - parentInsets.left - parentInsets.right,parent->getBounds().height - parentInsets.top - parentInsets.bottom);
			
			int y = parentInsets.top;

			ComponentList::const_iterator iter;
			ComponentList list = parent->getChildren();

			ComponentList row;

			for(iter = list.begin(); iter != list.end(); ++iter)
			{
				if((*iter)->isVisible())
				{
					(*iter)->setSize((*iter)->getPreferredSize());
					row.push_back((*iter));

					rowDimension.height = std::max(rowDimension.height,(*iter)->getPreferredSize().height + getVgap());
					rowDimension.width += (*iter)->getPreferredSize().width + getHgap();

					if(rowDimension.width > parent->getBounds().width + (parentInsets.left + parentInsets.right))
					{
						align(row,y,parentInsets,rowDimension,parentDimension);
						row.clear();

						y += rowDimension.height;
						rowDimension.width = 0;
						rowDimension.height = 0;
					}
				}
			}
			align(row,y,parentInsets,rowDimension, parentDimension);
		}

		void FlowLayout::align(ComponentList &row, int rowHeight, util::Insets &parentInsets, util::Dimension &rowDimension, util::Dimension &parentDimension)
		{
			util::Point location(parentInsets.left,0);

			switch(alignment)
			{
				case Component::CENTER:
				{
					location.x = (getHgap() + parentDimension.width - rowDimension.width) / 2;
					break;
				}
				case Component::LEFT:
				{
					location.x = getHgap();
					break;
				}
				case Component::RIGHT:
				{
					location.x = (parentDimension.width - rowDimension.width);
					break;
				}
			}

			ComponentList::const_iterator rowIterator;

			for(rowIterator = row.begin(); rowIterator != row.end(); ++rowIterator)
			{
				location.y = rowHeight + ((parentDimension.height / 2) - ((*rowIterator)->getBounds().height / 2));
				(*rowIterator)->setLocation(location);
				location.x += (*rowIterator)->getBounds().width + getHgap();				
			}
		}
/*
		void FlowLayout::moveComponents(Container* parent, int x, int y, int width, int height, int rowStart, int rowEnd)
		{
			switch(alignment)
			{
				case Component::CENTER:
				{
					x += width/2;
					break;
				}
				case Component::LEFT:
				{
					x += 0;
					break;
				}
				case Component::RIGHT:
				{
					x += width;
					break;
				}
			}

			for(int i = rowStart; i < rowEnd; ++i)
			{
				Component* comp = parent->getChild(i);

				if(comp->isVisible())
				{
					comp->setLocation(x,y + (height - comp->getPreferredSize().height) /2);
					x += comp->getPreferredSize().width + getHgap();
				}
			}
		}
		*/
	}
}