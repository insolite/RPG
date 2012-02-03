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
#include "./TextField.h"
#include "../event/PropertyEvent.h"

namespace ui
{
	TextField::TextField()
	{
		init("");
	}

	TextField::TextField(const std::string &text)
	{
		init(text);
	}

	void TextField::init(const std::string &text)
	{
		setThemeName("TextField");
		setText(text);
		echoCharacter = 0;
		listener.setParent(this);
	}

	void TextField::setText(const std::string &t)
	{
		text = t;
		event::PropertyEvent e(this,event::PropertyEvent::SPECIAL,TextField::TEXTCHANGE);
		processPropertyEvent(e);
	}

	const std::string & TextField::getText() const
	{
		return text;
	}

	void TextField::setEchoCharacter(int c)
	{
		echoCharacter = c;
	}

	int TextField::getEchoCharacter() const
	{
		return echoCharacter;
	}

	bool TextField::hasEchoCharacter() const
	{
		return (echoCharacter != 0);
	}

	// ------------------------------------------------------

	TextField::TextListener::TextListener()
		:	parent(0)
	{
	}

	void TextField::TextListener::setParent(TextField *textField)
	{
		if(parent != 0)
		{
			parent->removeKeyListener(this);
		}
		parent = textField;
		textField->addKeyListener(this);
	}

	TextField * TextField::TextListener::getParent() const
	{
		return parent;
	}

	void TextField::TextListener::keyPressed(const event::KeyEvent &e)
	{
		TextField *textField(static_cast<TextField*>(e.getSource()));

		std::string str(textField->getText());

		if(e.getKeyCode() == event::KeyEvent::VKUI_BACKSPACE)
		{
					// backspace
			str = str.substr(0,str.length()-1);
		//	cursorPosition--;
		//	cursorPosition = std::max(0,cursorPosition);
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
		//	cursorPosition++;
		}
		textField->setText(str);
	}

	void TextField::TextListener::keyReleased(const event::KeyEvent &e)
	{
	}

	void TextField::TextListener::keyTyped(const event::KeyEvent &e)
	{
	}
}