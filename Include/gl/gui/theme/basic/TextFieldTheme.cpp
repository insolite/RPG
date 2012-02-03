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
#include "./TextFieldTheme.h"
#include "../../Component.h"
#include "../../component/TextField.h"
#include "../../Font.h"
#include "../../GlyphContext.h"
#include "../../Graphics.h"
#include "../../event/KeyEvent.h"
#include "../../event/FocusEvent.h"

namespace ui
{
	namespace theme
	{
		namespace basic
		{
			void TextFieldTheme::installTheme(Component *comp)
			{
				comp->setBorder(&border);
				comp->addFocusListener(this);
				comp->addMouseListener(this);
				comp->addInterpolator(&interpolator);
				comp->setFont(GlyphContext::getInstance().createFont("Vera.ttf",10)); // default font
			}

			void TextFieldTheme::deinstallTheme(Component *comp)
			{
				comp->removeFocusListener(this);
				comp->removeMouseListener(this);
				comp->removeInterpolator(&interpolator);
			}

			void TextFieldTheme::paint(Graphics &g, const Component *comp) const
			{
				BasicComponent::paint(g,comp);

				const TextField *textField = static_cast<const TextField*>(comp);

				g.enableScissor(textField->getLocationOnScreen().x,textField->getLocationOnScreen().y,textField->getBounds().width,textField->getBounds().height);

				g.setPaint(textField->getForeground());
				std::string text = textField->getText();
				Font *f = textField->getFont();
				g.setFont(f);

				if(textField->hasEchoCharacter())
				{
					//std::size_t length = text.length();
					text = std::string(text.length(),static_cast<char>(textField->getEchoCharacter()));
				}
				util::Dimension bbox(f->getStringBoundingBox(text));
				int y = textField->getBounds().height / 2 - bbox.height/2;
				g.drawString(textField->getInsets().left,y,text);
				if(displayCursor && textField->hasFocus())
				{
					int border = 4;
					g.fillRect(2 + bbox.width,border,2,textField->getBounds().height - border - border);
				}
				g.disableScissor();
			}

			const util::Dimension TextFieldTheme::getPreferredSize(const Component *comp) const
			{
				const TextField *textField = static_cast<const TextField*>(comp);

				std::string text = textField->getText();
				Font *f = textField->getFont();

				util::Dimension bbox(f->getStringBoundingBox(text));
				int height= bbox.height + textField->getInsets().top + textField->getInsets().bottom; 	

				return util::Dimension(140,height);
			}

			void TextFieldTheme::propertyChanged(const event::PropertyEvent &e)
			{
			}

			TextFieldTheme::TextFieldTheme()
				:	border(util::Color(255,255,255),1),
					interpolator(1.0f,0,100.0f),
					displayCursor(false)
			{
				interpolator.addInterpolatee(this);
				interpolator.start();
			}

			TextFieldTheme::~TextFieldTheme()
			{
				interpolator.removeInterpolatee(this);
			}

			void TextFieldTheme::update(float value)
			{
				if(value == 100.0f)
				{
					displayCursor = !displayCursor;
					interpolator.reset();
				}
			}

			void TextFieldTheme::focusGained(const event::FocusEvent &e)
			{
				TextField *textField(static_cast<TextField*>(e.getSource()));
				cursorPosition = static_cast<int>(textField->getText().length());
			}

			void TextFieldTheme::focusLost(const event::FocusEvent &e)
			{
			}
		}
	}
}