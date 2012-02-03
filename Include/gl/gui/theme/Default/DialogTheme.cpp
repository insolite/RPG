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
#include "../../Graphics.h"
#include "../../border/BevelBorder.h"
#include "../../component/Dialog.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			void DialogTheme::installTheme(Component *comp)
			{
				Dialog *dialog = static_cast<Dialog*>(comp);
				dialog->setBorder(&border);
				dialog->addWindowListener(this);
				//dialog->getTitleBar()->getCloseButton()->addMouseListener(this);
				//dialog->setRotation(45.0f);
				//dialog->setTransparency(0.5f);
			}

			void DialogTheme::deinstallTheme(Component *comp)
			{
				Dialog *dialog = static_cast<Dialog*>(comp);
				dialog->removeWindowListener(this);
				dialog->getTitleBar()->getCloseButton()->removeMouseListener(this);
			}

			void DialogTheme::mouseReleased(const event::MouseEvent &e)
			{
				//Dialog *dialog = static_cast<Dialog*>(e.getSource());
				// this is a bit of a hack..
				//dialog->hide();
			}

			DialogTheme::DialogTheme()
				:	activeBackground(util::Color(221,221,236),util::Color(169,169,189),util::GradientColor::DEGREES_90),
					inactiveBackground(util::Color(224,224,224),util::Color(180,180,180),util::GradientColor::DEGREES_90),
					shadow(0,0,0,50)

			{
			}

			void DialogTheme::windowActivated(const event::WindowEvent &e)
			{
				Dialog *dialog = static_cast<Dialog*>(e.getSource());
				// this is a bit of a hack..
				dialog->getTitleBar()->getTitleLabel()->setBackground(SchemeManager::getInstance().getScheme()->getTitleBarSelected());
			}

			void DialogTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				g.setPaint(&shadow);
			//	int size = 5;
				g.fillRect(1,1,comp->getBounds().width,comp->getBounds().height);
				shadow.alpha = (float)40/255;
				g.fillRect(2,2,comp->getBounds().width,comp->getBounds().height);
				shadow.alpha = (float)20/255;
				g.fillRect(3,3,comp->getBounds().width,comp->getBounds().height);
				shadow.alpha = (float)10/255;
				g.fillRect(4,4,comp->getBounds().width,comp->getBounds().height);
				shadow.alpha = (float)10/255;
				g.fillRect(5,5,comp->getBounds().width,comp->getBounds().height);
				shadow.alpha = (float)50/255;
			//	g.popMatrix();
			/*
				glClear(GL_ACCUM_BUFFER_BIT);
				g.setPaint(&shadow);
				//shadow.alpha
				
				for(int i = 1; i < size; ++i)
				{
					
					glTranslatef(i,i,0.0f);
					g.fillRect(0,0,comp->getBounds().width,comp->getBounds().height);
					glTranslatef(-i,-i,0.0f);
			
					glAccum(GL_ACCUM,0.25f);
				}
				glAccum(GL_RETURN,1.0f);
				*/
			}

			void DialogTheme::windowDeactivated(const event::WindowEvent &e)
			{
				Dialog *dialog = static_cast<Dialog*>(e.getSource());
				dialog->getTitleBar()->getTitleLabel()->setBackground(SchemeManager::getInstance().getScheme()->getTitleBarDeselected());
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