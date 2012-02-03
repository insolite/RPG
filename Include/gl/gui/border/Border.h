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

#ifndef BORDER_H
#define BORDER_H

#include "../Pointers.h"
#include "../util/Insets.h"

namespace ui
{
	/**
	 * Border namespace, contains all
	 * border related code.
	 */
	namespace border
	{
		/**
		 * Border interface.
		 * You can instantiate this, but it won't do jack.
		 */
		class Border
		{
		public:
			/**
			 * Default Constructor.
			 */
			Border();

			/**
			 * Copy Constructor.
			 */
			Border(const Border& rhs);

			/**
			 * Assignment Operator.
			 */
			Border& operator=(const Border& rhs);

			/**
			 * Swap the content of this border with another.
			 */
			void swap(Border& rhs) throw();

			/**
			 * Paints a Border around the specified Component.
			 */
			virtual void paintBorder(const Component* component, Graphics& g, int x, int y, int w, int h) const;

			/**
			 * Returns the Insets used by this Border.
			 */
			virtual const util::Insets getBorderInsets() const;

			/**
			 * Destructor.
			 */
			virtual ~Border();
		};
	}
}
#endif