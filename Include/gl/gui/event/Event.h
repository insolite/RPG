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

#ifndef EVENT_H
#define EVENT_H

#include "../Pointers.h"

namespace ui
{
	/**
	 * This namespace holds all event related code.
	 */
	namespace event
	{
		/**
		 * Common abstract Event class.
		 * This is the base class for all events that
		 * are sent through the GUI.
		 */
		class Event
		{
		public:
			/**
			 * Create a new Event with given source Component,
			 * and identifier.
			 * @param
			 *	source the Component from which the Event originated.
			 * @param
			 *	id Identifier which can be used to identify the Event type.
			 */
			Event(Component* source, int id)
			{
				this->source = source;
				this->eventId = id;
			}

			/**
			 * Return a pointer to the source Component.
			 * @return
			 *	A pointer to the Component from which the event
			 *	originated.
			 */
			Component* getSource() const
			{
				return source;
			}

			/**
			 * Returns the Event identifier.
			 * @return
			 *	An identifier which can be used to determine the nature of the Event.	
			 */
			int getID() const
			{
				return eventId;
			}
		private:
			int eventId;
			Component* source;
		};
	}
}

#endif