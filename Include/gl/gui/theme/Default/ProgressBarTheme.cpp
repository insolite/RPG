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
#include "./ProgressBarTheme.h"
#include "../../component/ProgressBar.h"
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
			ProgressBarTheme::ProgressBarTheme()
				:	background(224,224,224),
					foreground(0,0,0),
					barColor(139,178,206),
					borderColor(128,128,128),
					border(borderColor,1) // is this dangerous? initialization order?
			{
			}
			
			void ProgressBarTheme::installTheme(Component *comp)
			{
				ProgressBar *progressBar = static_cast<ProgressBar*>(comp);
			//	progressBar->setBackground(&background);
			//	progressBar->setForeground(&foreground);
				progressBar->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
				progressBar->setBorder(&border);
			}
			
			void ProgressBarTheme::deinstallTheme(Component *comp)
			{
			}
			
			const util::Dimension ProgressBarTheme::getPreferredSize(const Component *comp) const
			{
				const ProgressBar *progressBar = static_cast<const ProgressBar*>(comp);

				util::Dimension ret;
				util::Dimension bbox(progressBar->getFont()->getStringBoundingBox("00%"));

				if(progressBar->getOrientation() == ProgressBar::HORIZONTAL)
				{
					ret.width = 140;
					ret.height = bbox.height + progressBar->getInsets().bottom + progressBar->getInsets().top + 14;
				}
				else
				{
					ret.height = 140;
					ret.width = bbox.width + progressBar->getInsets().left + progressBar->getInsets().right + 14;
				}
				return ret;
			}
			
			void ProgressBarTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const ProgressBar *progressBar = static_cast<const ProgressBar*>(comp);

				// calculate the percentage
				float tmp = ((float)(progressBar->getValue()-progressBar->getMinimum()) / (float)(progressBar->getMaximum()-progressBar->getMinimum()));
				
				g.setPaint(SchemeManager::getInstance().getScheme()->getHighlight());
				if(progressBar->getOrientation() == ProgressBar::VERTICAL)
				{
					int percentage = (int) (tmp * progressBar->getBounds().height);
					g.fillRect(0,progressBar->getBounds().height-percentage,progressBar->getBounds().width,percentage);
				}
				else
				{
					int percentage = (int) (tmp * progressBar->getBounds().width);
					g.fillRect(0,0,percentage,progressBar->getBounds().height);
				}

				if(progressBar->isStringPainted())
				{
					// find proper string location
					int percent =  (int)(tmp * 100);

					std::ostringstream s;
					s << percent << "%";

					std::string p = s.str();

					util::Dimension bbox(progressBar->getFont()->getStringBoundingBox(p));

					int x = progressBar->getBounds().width /2 - bbox.width/2;
					int y = progressBar->getBounds().height/2 - bbox.height/2;

					g.setPaint(progressBar->getForeground());
					g.drawString(x,y,p);
				}

			}
		}
	}
}