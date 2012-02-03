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
#include "./ScrollbarTheme.h"
#include "../../Component.h"
#include "../../component/Scrollbar.h"
#include "../../Graphics.h"
#include "../../event/MouseEvent.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			ScrollbarTheme::ScrollbarTheme()
				:	lineColor(130,130,130),
					border(lineColor,0)
			{
			}

			ScrollbarTheme::~ScrollbarTheme()
			{
			}

			void ScrollbarTheme::installTheme(Component *comp)
			{
				//comp->addMouseListener(this);
				//comp->setBorderPainted(false);
				Scrollbar * scrollbar = static_cast<Scrollbar*>(comp);

				scrollbar->setBorder(&border);

				scrollbar->getIncrementButton()->setDefaultIcon(&incrementIcon);
				scrollbar->getIncrementButton()->setSelectedIcon(&incrementIcon);
				scrollbar->getIncrementButton()->setMargin(util::Insets(0,0,0,0));
				scrollbar->getIncrementButton()->setFocusPainted(false);
			//	incrementIcon.setOrientation(scrollbar->getOrientation());

				scrollbar->getDecrementButton()->setDefaultIcon(&decrementIcon);
				scrollbar->getDecrementButton()->setSelectedIcon(&decrementIcon);
				scrollbar->getDecrementButton()->setMargin(util::Insets(0,0,0,0));
				scrollbar->getDecrementButton()->setFocusPainted(false);
			//	decrementIcon.setOrientation(scrollbar->getOrientation());
			}

			void ScrollbarTheme::deinstallTheme(Component *comp)
			{
				//comp->removeMouseListener(this);
			}

			const util::Dimension ScrollbarTheme::getPreferredSize(const Component *comp) const
			{
				const Scrollbar * scrollbar = static_cast<const Scrollbar*>(comp);

				if(scrollbar->getOrientation() == Scrollbar::HORIZONTAL)
				{
					return util::Dimension(140,20);
				}
				else
				{
					return util::Dimension(20,140);
				}
			}

			void ScrollbarTheme::paint(Graphics &g, const Component *comp) const
			{
				const Scrollbar * scrollbar = static_cast<const Scrollbar*>(comp);

				incrementIcon.setOrientation(scrollbar->getOrientation());
				decrementIcon.setOrientation(scrollbar->getOrientation());

				ComponentTheme::paint(g,comp);
			}

			int ScrollbarTheme::IncrementIcon::getIconHeight() const
			{
				return 16;
			}

			int ScrollbarTheme::IncrementIcon::getIconWidth() const
			{
				return 16;
			}

			void ScrollbarTheme::IncrementIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				g.setPaint(&foreground);
				if(orientation == Scroller::VERTICAL)
				{
					// hurray for magical numbers :s
					g.translate(20,0);
					g.rotate(90.0f);
				}
				g.drawImage(textureId,x,y,textureWidth,textureHeight);

				if(orientation == Scroller::VERTICAL)
				{
					g.rotate(-90.0f);
					g.translate(-20,0);
				}
			}

			void ScrollbarTheme::IncrementIcon::setOrientation(int o)
			{
				orientation = o;
			}

			ScrollbarTheme::IncrementIcon::IncrementIcon()
				:	foreground(0,0,0),
				orientation(Scroller::HORIZONTAL)
			{
				GLubyte texture[textureWidth][textureHeight] = 
				{
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  }
				};

				GLubyte uploadTexture[textureWidth][textureHeight][4];

				for(int width = 0; width < textureWidth; ++width)
				{
					for(int height = 0; height < textureHeight; ++height)
					{
						uploadTexture[width][height][0] = 255;
						uploadTexture[width][height][1] = 255;
						uploadTexture[width][height][2] = 255;
						uploadTexture[width][height][3] = texture[width][height];
					}
				}

				glGenTextures(1,&textureId);
				glBindTexture(GL_TEXTURE_2D,textureId);
			
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, uploadTexture);
			
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

// -------------------------------------------------------------------------------

			int ScrollbarTheme::DecrementIcon::getIconHeight() const
			{
				return 16;
			}

			int ScrollbarTheme::DecrementIcon::getIconWidth() const
			{
				return 16;
			}

			void ScrollbarTheme::DecrementIcon::setOrientation(int o)
			{
				orientation = o;
			}
			
			void ScrollbarTheme::DecrementIcon::paint(const Component *comp, Graphics &g, int x, int y) const
			{
				g.setPaint(&foreground);
				if(orientation == Scroller::VERTICAL)
				{
					// hurray for magical numbers :s
					g.translate(20,0);
					g.rotate(90.0f);
				}
				g.drawImage(textureId,x,y,textureWidth,textureHeight);

				if(orientation == Scroller::VERTICAL)
				{
					g.rotate(-90.0f);
					g.translate(-20,0);
				}
			}

			ScrollbarTheme::DecrementIcon::DecrementIcon()
				:	foreground(0,0,0),
					orientation(Scroller::HORIZONTAL)
			{
				GLubyte texture[textureWidth][textureHeight] = 
				{
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 255, 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  },
					{ 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  }
				};

				GLubyte uploadTexture[textureWidth][textureHeight][4];

				for(int width = 0; width < textureWidth; ++width)
				{
					for(int height = 0; height < textureHeight; ++height)
					{
						uploadTexture[width][height][0] = 255;
						uploadTexture[width][height][1] = 255;
						uploadTexture[width][height][2] = 255;
						uploadTexture[width][height][3] = texture[width][height];
					}
				}

				glGenTextures(1,&textureId);
				glBindTexture(GL_TEXTURE_2D,textureId);
			
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, uploadTexture);
			
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

		}
	}
}