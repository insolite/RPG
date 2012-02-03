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
#include "./BorderLayout.h"
#include "../Container.h"
#include "../util/Insets.h"
#include "../util/Rectangle.h"
#include "../util/Dimension.h"

namespace ui
{
	namespace layout
	{
		void BorderLayout::layoutContainer(const Container* parent)
		{	
			int top = parent->getInsets().top;
			int bottom = parent->getBounds().height - parent->getInsets().bottom;
			int left = parent->getInsets().left;
			int right = parent->getBounds().width - parent->getInsets().right;

			if(north != 0 && north->isVisible())
			{
				north->setSize(right - left, north->getBounds().height);
				north->setBounds(left,top,right - left,north->getPreferredSize().height);
				top += north->getPreferredSize().height + getVgap();
			}

			if(south != 0 && south->isVisible())
			{
				south->setSize(right - left, south->getBounds().height);
				south->setBounds(left,bottom - south->getPreferredSize().height, right - left, south->getPreferredSize().height);
				bottom -= south->getPreferredSize().height + getVgap();
			}

			if(east != 0 && east->isVisible())
			{
				east->setSize(east->getBounds().width, bottom - top);
				east->setBounds(right- east->getPreferredSize().width,top,east->getPreferredSize().width, bottom - top);
				right -= east->getPreferredSize().width + getHgap();
			}

			if(west != 0 && west->isVisible())
			{
				west->setSize(west->getBounds().width, bottom - top);
				west->setBounds(left,top,west->getPreferredSize().width, bottom - top);
				left += west->getPreferredSize().width + getHgap();
			}

			if(center != 0 && center->isVisible())
			{
				center->setBounds(left,top,right - left, bottom - top);
			}

			if(!fillCorners)
			{
				// resize north and south
				if(west != 0 && west->isVisible())
				{
					if(north != 0 && north->isVisible())
					{
						north->setBounds(north->getBounds().x + west->getBounds().width,north->getBounds().y,north->getBounds().width - west->getBounds().width, north->getBounds().height);
					}

					if(south != 0 && south->isVisible())
					{
						south->setBounds(south->getBounds().x + west->getBounds().width,south->getBounds().y,south->getBounds().width - west->getBounds().width, south->getBounds().height);
					}
				}

				if(east != 0 && east->isVisible())
				{
					if(north != 0 && north->isVisible())
					{
						north->setBounds(north->getBounds().x,north->getBounds().y,north->getBounds().width - east->getBounds().width, north->getBounds().height);
					}

					if(south != 0 && south->isVisible())
					{
						south->setBounds(south->getBounds().x,south->getBounds().y,south->getBounds().width - east->getBounds().width, south->getBounds().height);
					}
				}
			}
		}

		const util::Dimension BorderLayout::preferredLayoutSize(const Container* parent) const
		{
			util::Dimension dim;
	
			if(east != 0 && east->isVisible())
			{
				dim.width += east->getPreferredSize().width + getHgap();
				dim.height = std::max(east->getPreferredSize().height,dim.height);

				if(!fillCorners)
				{
					dim.width += east->getPreferredSize().width;
				}
			}
			if(west != 0 && west->isVisible())
			{
				dim.width += west->getPreferredSize().width + getHgap(); 
				dim.height = std::max(west->getPreferredSize().height, dim.height);	   

				if(!fillCorners)
				{
					dim.width += west->getPreferredSize().width;
				}
			}
			if(center != 0 && center->isVisible())
			{
				dim.width += center->getPreferredSize().width;
				dim.height = std::max(center->getPreferredSize().height, dim.height);
			}
			if(north != 0 && north->isVisible())
			{
				dim.width = std::max(north->getPreferredSize().width,dim.width);
				dim.height += north->getPreferredSize().height + getVgap();
			}
			if(south != 0 && south->isVisible())
			{
				dim.width = std::max(south->getPreferredSize().width,dim.width);
				dim.height += south->getPreferredSize().height + getVgap();
			}

			dim.width += parent->getInsets().left + parent->getInsets().right;
			dim.height += parent->getInsets().top + parent->getInsets().bottom;
			
			return dim;
		}


		BorderLayout::BorderLayout()
			:	north(0),
				south(0),
				east(0),
				west(0),
				center(0),
				fillCorners(true)
		{
		}

		BorderLayout::BorderLayout(int hgap, int vgap)
			:	north(0),
				south(0),
				east(0),
				west(0),
				center(0),
				fillCorners(true)
		{
			setHgap(hgap);
			setVgap(vgap);
		}

		BorderLayout::BorderLayout(bool fill, int hgap, int vgap)
			:	north(0),
				south(0),
				east(0),
				west(0),
				center(0),
				fillCorners(fill)
		{
			setHgap(hgap);
			setVgap(vgap);
		}

		BorderLayout::BorderLayout(bool fill)
			:	north(0),
				south(0),
				east(0),
				west(0),
				center(0),
				fillCorners(fill)
		{
		}

		BorderLayout::BorderLayout(const BorderLayout& rhs)
			:	north(rhs.north),
				south(rhs.south),
				east(rhs.east),
				west(rhs.west),
				center(rhs.center),
				fillCorners(rhs.fillCorners)
		{
		}

		BorderLayout& BorderLayout::operator =(const BorderLayout& rhs)
		{
			BorderLayout temp(rhs);
			swap(temp);
			return *this;
		}

		void BorderLayout::swap(BorderLayout& rhs) throw()
		{
			std::swap(north,rhs.north);
			std::swap(south,rhs.south);
			std::swap(east,rhs.east);
			std::swap(west,rhs.west);
			std::swap(center,rhs.center);
			std::swap(fillCorners,rhs.fillCorners);
		}

		void BorderLayout::removeLayoutComponent(Component* comp)
		{
			if(north == comp)
				north = 0;
			else if(south == comp)
				south = 0;
			else if(east == comp)
				east = 0;
			else if(west == comp)
				west = 0;
			else if(center == comp)
				center = 0;
		}

		void BorderLayout::addLayoutComponent(Component* comp, int constraint)
		{
			if(constraint == -1)
				return;

			switch(constraint)
			{
				case NORTH:
				{
					north = comp;
					break;
				}
				case SOUTH:
				{
					south = comp;
					break;
				}
				case EAST:
				{
					east = comp;
					break;
				}
				case WEST:
				{
					west = comp;
					break;
				}
				case CENTER:
				{
					center = comp;
					break;
				}
			}
		}
	}
}