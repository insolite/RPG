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
#ifndef DIMENSION_H
#define DIMENSION_H

#include "../Pointers.h"

namespace ui
{
	namespace util
	{
		/**
		* Class representation of a 2d rectangular space.
		*/
		class Dimension
		{
		public:
			/**
			* Creates a new Rectangle with specified parameters.
			*/
			Dimension(int w, int h);

			/**
			 * Default constructor.
			 * Creates an empty dimension.
			 */
			Dimension();

			/**
			 * Copy constructor.
			 * Creates a new Dimension based
			 * on an existing.
			 */
			Dimension(const Dimension& rhs);

			/**
			 * Assignment operator.
			 * Assign one Dimension to another.
			 */
			Dimension& operator=(const Dimension& rhs);

			/**
			 * Compare two dimensions.
			 */
			bool operator==(const Dimension& rhs);

			/**
			 * Swaps two dimensions.
			 */
			void swap(Dimension& rhs) throw();

			/**
			 * Destructor.
			 */
			~Dimension();

			int width, height;
		};
	}
}
#endif