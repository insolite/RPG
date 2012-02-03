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

#ifndef INSETS_H
#define INSETS_H

#include "../Pointers.h"

namespace ui
{
	namespace util
	{
		/**
		* Insets defines space on four sides of a rectangle.
		* Insets are used for calculating border size, padding
		* and margins.
		*/
		class Insets
		{
		public:
			/**
			* Creates new Insets.
			* @param
			*	top defines top space.
			* @param
			*	left defines left space.
			* @param
			*	bottom defines bottom space.
			* @param
			*	right defines right space.
			*/
			Insets(int top, int left, int bottom, int right);
			
			/**
			 * Default constructor.
			 * Creates empty Insets.
			 */
			Insets();

			/**
			 * Copy Constructor.
			 */
			Insets(const Insets& rhs);

			/**
			 * Assignment operator.
			 */
			Insets& operator=(const Insets& rhs);

			/**
			 * Compare two insets.
			 */
			bool operator==(const Insets& rhs);

			/**
			 * Swaps the content of two insets.
			 */
			void swap(Insets& rhs) throw();

			/**
			 * Destructor.
			 */
			~Insets();

			int top,left,bottom,right;
		};
	}
}
#endif