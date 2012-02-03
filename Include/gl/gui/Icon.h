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

#ifndef ICON_H
#define ICON_H

#include "./Component.h"

namespace ui
{
	/** 
	 * Icon interface.
	 * By implementing this interface your object qualifies 
	 * as an Icon and can be used in Labels and Buttons.
	 * Besides icons, this can also be used to use images
	 * on buttons.
	 */
	class Icon
	{
	public:
		/**
		 * Paint the icon.
		 * @param
		 *	c Component the Icon is painted on.
		 * @param
		 *	g Graphics instance, used for drawing.
		 * @param
		 *	x X location of the icon.
		 * @param
		 *	y Y location of the icon.
		 */
		virtual void paint(const Component *c, Graphics&g, int x, int y) const = 0;

		/**
		 * Returns the preferred height for this Icon.
		 * This height is then used in calculating the icon's
		 * parent size.
		 */
		virtual int getIconHeight() const = 0;

		/**
		 * Returns the preferred width for this Icon.
		 * This width is then used in calculating the icon's
		 * parent size.
		 */
		virtual int getIconWidth() const = 0;
		
		virtual ~Icon() {};
	};
}

#endif