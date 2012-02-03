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
#include "./DialogTheme.h"
#include "../../Component.h"
#include "../../component/Dialog.h"

namespace ui
{
	namespace theme
	{
		namespace basic
		{
			void DialogTheme::installTheme(Component *comp)
			{
				Dialog *dialog = static_cast<Dialog*>(comp);
				dialog->setBorder(&border);
				dialog->addWindowListener(this);
			}

			void DialogTheme::deinstallTheme(Component *comp)
			{
				Dialog *dialog = static_cast<Dialog*>(comp);
				dialog->removeWindowListener(this);
			}

			DialogTheme::DialogTheme()
				:	black(0,0,0),
					white(255,255,255),
					border(white,5)

			{
			}

			void DialogTheme::windowActivated(const event::WindowEvent &e)
			{
				Dialog *dialog = static_cast<Dialog*>(e.getSource());
				// this is a bit of a hack..
				dialog->getTitleBar()->getTitleLabel()->setBackground(&white);
				dialog->getTitleBar()->getTitleLabel()->setForeground(&black);
			}

			void DialogTheme::windowDeactivated(const event::WindowEvent &e)
			{
				Dialog *dialog = static_cast<Dialog*>(e.getSource());
				dialog->getTitleBar()->getTitleLabel()->setBackground(&black);
				dialog->getTitleBar()->getTitleLabel()->setForeground(&white);
			}

			void DialogTheme::windowClosed(const event::WindowEvent &e)
			{
			}

			void DialogTheme::windowOpened(const event::WindowEvent &e)
			{
			}
		}
	}
}