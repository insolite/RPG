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

#ifndef UTIL_H
#define UTIL_H

#include "../../util/Point.h"
#include "../../util/Dimension.h"
#include "../../component/AbstractButton.h"
#include "../../component/MenuItem.h"
#include "../../component/Label.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			/**
			 * A collection of often used methods.
			 * Mostly for lazy programmers like me.
			 */
			class Util
			{
			public:
				static util::Point getButtonAlignment(const AbstractButton *button, const std::string &text, const util::Dimension &strbbox);
				// this will create a string that fits in the button
				static std::string getButtonString(const AbstractButton *button);
				static void paintButton(const AbstractButton *button, Graphics &g);
				static void paintMenuItem(const MenuItem *menuItem, Graphics &g);
				static const util::Dimension getButtonSize(const AbstractButton * button);
				
				
				
			private:
				static Icon * getActiveIcon(const AbstractButton *button);
				static void paintIcon(const AbstractButton *button, Graphics &g, const std::string &text);
			}; 
		}
	}
}

#endif