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
#ifndef SLIDERTHEME_H
#define SLIDERTHEME_H

#include "./ComponentTheme.h"
#include "../../event/MouseListener.h"
#include "../../util/GradientColor.h"
#include "../../util/Rectangle.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class SliderTheme : public ComponentTheme, public event::MouseAdapter
			{
			public:
				SliderTheme();
				~SliderTheme();
				void installTheme(Component *comp);
				void deinstallTheme(Component *comp);
				void paint(Graphics& g,const Component *comp) const;
				const util::Dimension getPreferredSize(const Component *comp) const;

			private:
				void mousePressed(const event::MouseEvent &e);
				void mouseReleased(const event::MouseEvent &e);
				void mouseMotion(const event::MouseEvent &e);
				void paintKnob(Graphics &g, int x, int y, int width, int height, bool dragging) const;
				util::Color raisedShadow;
				util::Color raisedHighlight;
				util::GradientColor backgroundRaised;
				util::GradientColor backgroundLowered;
				util::Dimension sliderKnob;
				util::Color background;
			};
		}
	}
}

#endif