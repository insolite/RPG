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

#ifndef LINEBORDER_H
#define LINEBORDER_H

#include "Border.h"
#include "../util/Color.h"
#include "../util/Insets.h"

namespace ui
{
	namespace border
	{
		/**
		 * A simple border, consisting of only a single line.
		 * This line can have a color and a certain thickness.
		 */
		class LineBorder : public Border
		{
			public:
				/**
				 * Create a new LineBorder with given color
				 * and thickness.
				 * @param
				 *	color Color for the border.
				 * @param
				 *	thickness line thickness.
				 * @note
				 *	Note that the thickness affects the Insets.
				 */
				LineBorder(const util::Color& color, int thickness);

				/**
				 * Create a new LineBorder with given color
				 * and thickness.
				 * @param
				 *	color Color for the border.
				 * @param
				 *	thickness line thickness.
				 * @note
				 *	Note that the thickness affects the Insets.
				 */
				LineBorder(const util::Color &colo, const util::Insets &insets);

				/**
				 * Create a new LineBorder with given color.
				 * @param
				 *	color Color for the border.
				 */
				LineBorder(const util::Color& color);

				/**
				 * Default constructor.
				 */
				LineBorder();

				/**
				 * Copy Constructor.
				 */
				LineBorder(const LineBorder& rhs);

				/**
				 * Assignment operator.
				 */
				LineBorder& operator=(const LineBorder& rhs);

				/**
				 * Swaps the contents of this Border with another.
				 */
				void swap(LineBorder& rhs) throw();

				/**
				 * Paint the border.
				 */
				void paintBorder(const Component* component, Graphics& g, int x, int y, int w, int h) const;

				/**
				 * Returns the insets of this Border.
				 * The Insets are dependant on the thickness of this Border.
				 */
				const util::Insets getBorderInsets() const;

				/**
				 * Returns the Color used for this Border.
				 */
				const util::Color& getColor() const;

				void setColor(const util::Color &c);
			private:
				util::Color color;
				util::Insets insets;
		};
	}
}

#endif