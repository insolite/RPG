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
		namespace defaulttheme
		{
			void TextFieldTheme::installTheme(Component *comp)
			{
				comp->setBorder(&border);
				comp->setBackground(SchemeManager::getInstance().getScheme()->getTextBackground());
				//comp->setForeground(&foreground);
				comp->addKeyListener(this);
				comp->addFocusListener(this);
				comp->addMouseListener(this);
				comp->addInterpolator(&interpolator);
				comp->setFont(SchemeManager::getInstance().getScheme()->getDefaultFont()); // default font
			}

			void TextFieldTheme::deinstallTheme(Component *comp)
			{
				comp->removeKeyListener(this);
				comp->removeFocusListener(this);
				comp->removeMouseListener(this);
				comp->removeInterpolator(&interpolator);
			}

			void TextFieldTheme::paint(Graphics &g, const Component *comp) const
			{
				ComponentTheme::paint(g,comp);

				const TextField *textField = static_cast<const TextField*>(comp);

				g.enableScissor(textField->getLocationOnScreen().x,textField->getLocationOnScreen().y,textField->getBounds().width,textField->getBounds().height);

				g.setPaint(&foreground);
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
				//int width = bbox.width + textField->getMargin().left + textField->getMargin().right + textField->getInsets().left + textField->getInsets().right;
				int height= bbox.height + textField->getInsets().top + textField->getInsets().bottom; 	

				return util::Dimension(140,height);
			}

			void TextFieldTheme::propertyChanged(const event::PropertyEvent &e)
			{
			}

			TextFieldTheme::TextFieldTheme()
				:	foreground(0,0,0),
					background(util::Color(192,192,192),util::Color(255,255,255)),
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

			void TextFieldTheme::keyPressed(const event::KeyEvent &e)
			{
				TextField *textField(static_cast<TextField*>(e.getSource()));

				std::string str(textField->getText());

				if(e.getKeyCode() == event::KeyEvent::VKUI_BACKSPACE)
				{
					// backspace
					str = str.substr(0,str.length()-1);
					cursorPosition--;
					cursorPosition = std::max(0,cursorPosition);
				}
				else if(e.getKeyCode() == event::KeyEvent::VKUI_LEFT)
				{
					// move the cursor left
				}
				else if(e.getKeyCode() == event::KeyEvent::VKUI_RIGHT)
				{
				}
				else if((e.getKeyCode() == event::KeyEvent::VKUI_UP) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_DOWN) ||
					(e.getKeyCode() == 0) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_BREAK) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_RSHIFT) || 
					(e.getKeyCode() == event::KeyEvent::VKUI_LSHIFT) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_CAPSLOCK) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_ESCAPE) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_UNKNOWN) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_RETURN) ||
					(e.getKeyCode() == event::KeyEvent::VKUI_TAB))

				{
					// keys we just ignore
				//	int x = 0;
				}
				else
				{
					// normal keys
					std::string tmp(1,(char)e.getKeyCode());
					// check for uppercase
					if((e.getModifier() & event::KeyEvent::MOD_LSHIFT) ||
					(e.getModifier() & event::KeyEvent::MOD_RSHIFT) ||
					(e.getModifier() & event::KeyEvent::MOD_CAPS))
					{
						std::transform(tmp.begin(),tmp.end(),tmp.begin(),toupper);
					}
					str.append(tmp);
					cursorPosition++;
				}
				textField->setText(str);
			}

			void TextFieldTheme::update(float value)
			{
				if(value == 100.0f)
				{
					displayCursor = !displayCursor;
					interpolator.reset();
				}
			}

			void TextFieldTheme::keyReleased(const event::KeyEvent &e)
			{
			}

			void TextFieldTheme::keyTyped(const event::KeyEvent &e)
			{
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