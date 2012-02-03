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

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "../Pointers.h"

namespace ui
{
	namespace util
	{
		/**
		 * Item that can be observed by an Observer.
		 * Once this Item is changed, the Observer is
		 * notified that a change has occured, and can take
		 * appropiate action. This is to loosen coupling of
		 * classes, as an Observer knows nothing about it's
		 * observable and visa vice.
		 */
		class Observable
		{
		public:
			/**
			 * Add an Observer to this Observable.
			 * @param
			 *	observer the Observer to add.
			 */
			void addObserver(Observer* observer);

			/**
			 * Remove an Observer from this Observable.
			 * @param
			 *	observer The Observer to remove.
			 */
			void removeObserver(Observer* observer);

			/**
			 * Remove all Observers from this Observable.
			 */
			void removeObservers();

			/**
			 * Notify the Observers of a change.
			 * The Observers are only called when
			 * the isChanged flag is set to true.
			 * @see
			 *	setChanged, hasChanged, clearChanged
			 */
			void notifyObserver();

			/**
			 * Destructor.
			 */
			virtual ~Observable();
		protected:
			/**
			 * Sets the isChanged flag to true.
			 * Next time the notifyObserver method is
			 * called, the Observers will be notified of the change.
			 */
			void setChanged();

			/**
			 * Returns the isChanged flag.
			 */
			bool hasChanged() const;

			/**
			 * Set the isChanged flag to false.
			 */
			void clearChanged();

			/**
			 * Default constructor.
			 */
			Observable();
		private:
			bool isChanged;
			ObserverList observerList;
		};
	}
}

#endif