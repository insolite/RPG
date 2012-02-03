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
#ifndef DIALOGTHEME_H
#define DIALOGTHEME_H

#include "./ComponentTheme.h"
#include "../../util/Color.h"
#include "../../util/GradientColor.h"
#include "../../border/BevelBorder.h"
#include "../../event/WindowListener.h"
#include "../../event/WindowEvent.h"
#include "../../event/MouseListener.h"
#include "../../event/MouseEvent.h"


namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			class DialogTheme :	public ComponentTheme, public event::WindowListener, public event::MouseAdapter
			{
			public:
				DialogTheme();
				void installTheme(Component *comp);
				void deinstallTheme(Component *comp);

			private:
				void windowClosed(const event::WindowEvent &e);
				void windowOpened(const event::WindowEvent &e);
				void windowActivated(const event::WindowEvent &e);
				void windowDeactivated(const event::WindowEvent &e);
				border::BevelBorder border;
				void paint(Graphics &g, const Component *comp) const;

				void mouseReleased(const event::MouseEvent &e);

				util::GradientColor activeBackground;
				util::GradientColor inactiveBackground;
				mutable util::Color shadow;
			};
		}
	}
}

#endif