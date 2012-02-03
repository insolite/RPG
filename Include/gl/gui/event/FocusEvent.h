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

#ifndef FOCUSEVENT_H
#define FOCUSEVENT_H

#include "../Pointers.h"
#include "./Event.h"


namespace ui
{
	namespace event
	{
		/**
		 * An event indicating that a Component has lost or gained
		 * focus. Focus can be received in several ways, including
		 * mouse clicks and keyboard input.
		 */
		class FocusEvent : public Event
		{
		public:
			enum
			{
				/**
				 * Identifier indicating a focus gained event.
				 */
				FOCUS_GAINED,
				/**
				 * Identifier indicating a focus lost event.
				 */
				FOCUS_LOST
			} FocusEventTypes;

			/**
			 * Create a new FocusEvent.
			 * @param
			 *	source Event from where the event originated
			 * @param
			 *	id Event identifier, either FOCUS_LOST or FOCUS_GAINED
			 * @param
			 * temporary bool determining wether this is a temporary FocusEvent.
			 */
			FocusEvent(Component* source, int id, bool temporary);

			/**
			 * Create a new FocusEvent.
			 * @param
			 *	source Event from where the event originated
			 * @param
			 *	id Event identifier, either FOCUS_LOST or FOCUS_GAINED
			 * @param
			 * temporary bool determining wether this is a temporary FocusEvent.
			 */
			FocusEvent(Component* source, int id, bool temporary, Component* opposite);

			/**
			 * Returns true if this is a temporary FocusEvent.
			 */
			bool isTemporary() const;

			/**
			 * Returns the opposite Component, that is the Component
			 * which should receive focus after this Component.
			 * @return
			 *	A pointer to the opposite component.
			 */
			const Component* getOppositeComponent() const;
		private:
			bool temp;
			Component* opposite;
		};
	}
}
#endif