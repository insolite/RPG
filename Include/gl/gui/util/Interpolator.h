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

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "../Pointers.h"

namespace ui
{
	namespace util
	{
		/**
		 * By implementing this interface, your
		 * object can be interpolated once added to
		 * and interpolator.
		 * @see
		 *	Interpolator.
		 * @note
		 *	Is interpolatee proper engrish?
		 */
		class Interpolatee
		{
		public:
			virtual void update(float value) = 0;
			virtual ~Interpolatee() {};
		};

		/**
		 * Interpolates values, bases on input.
		 * This can be used for animating objects.
		 * Original idea from the gamedev article by Richard Fine.
		 * http://www.gamedev.net/reference/articles/article2011.asp
		 */
		class Interpolator
		{
		public:
			/**
			 * Creates an interpolator that interpolates
			 * the given value.
			 */
			Interpolator();

			/**
			 * Destructor.
			 */
			virtual ~Interpolator();

			/**
			 * Start interpolating.
			 */
			void start();

			/**
			 * Stop interpolating.
			 * This does not reset the timer.
			 */
			void stop();

			/**
			 * Update the interpolator value.
			 * @param
			 *	deltaTime time to use.
			 */
			virtual void update(float deltaTime) = 0;

			/**
			 * Register an interpolatee to this interpolator, which
			 * will be interpolated according to the interpolator
			 * type.
			 */
			void addInterpolatee(Interpolatee *interpolatee);

			/**
			 * Remove an interpolatee from this interpolator.
			 */
			void removeInterpolatee(Interpolatee *interpolatee);
		protected:
			/**
			 * Clamp a value between min and max values.
			 * @param
			 *	val the value to clamp.
			 * @param
			 *	min the minimum value to clamp to.
			 * @param
			 *	max the maximum value to clamp to.
			 */
			float clamp(float val, float min, float max);

			/**
			 * Indicates if this Interpolator is running.
			 */
			bool isRunning;

			std::vector<Interpolatee*> interpolateeList;
		};
	}
}
#endif