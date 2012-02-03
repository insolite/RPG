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

#ifndef BUTTON_H
#define BUTTON_H

#include "./AbstractButton.h"
#include "../event/MouseListener.h"
#include "../event/FocusListener.h"

namespace ui
{
	/**
	 * A normal, clickable button.
	 * This Button defines basic Button behaviour.
	 */
	class Button : public AbstractButton, public event::MouseAdapter, public event::FocusListener
	{
	public:
		/**
		 * Creates a new button with the given
		 * label.
		 * @param
		 * label the string to use as button label.
		 */
		Button(const std::string &label);
		
		/**
		 * Creates a new button with the given
		 * label and icon.
		 * @param
		 *	label The string to use as button label.
		 * @param
		 *	icon The Icon to use as button Icon.
		 */
		Button(Icon *icon, const std::string &label);
	private:
		void init(Icon *icon, const std::string &label);
		void mousePressed(const event::MouseEvent& e);
		void mouseReleased(const event::MouseEvent& e);

		void focusGained(const event::FocusEvent& e);
		void focusLost(const event::FocusEvent& e);
	};
}

#endif