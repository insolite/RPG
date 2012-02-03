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
#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include "../component/ToggleButton.h"
#include "../event/ItemListener.h"

namespace ui
{
	namespace util
	{
		/**
		* A group of ToggleButtons from which only one
		* can be selected. Once one is selected, the others
		* are deselected.
		* @note Note that this class is not part of the Component hierarchy,
		* and thus must be managed by the user. This means its memory
		* must be freed after it's used.
		*/
		class ButtonGroup : public event::ItemListener
		{
		public:
			/**
			* Add a ToggleButton to the group.
			* @param
			* button The ToggleButton derivative to add to this group.
			*/
			void add(ToggleButton* button);

			/**
			* Returns the number of ToggleButtons in
			* this group.
			* @return the number of buttons in this group.
			*/
			int getButtonCount();

			/**
			* Removes a ToggleButton from this group.
			* @param 
			* button The ToggleButton derivative to remove from this group.
			*/
			void remove(ToggleButton* button);

			virtual ~ButtonGroup() {};
		private:
			/**
			* Called when one of the ToggleButtons
			* receive an ItemEvent.
			*/
 			void itemStateChanged(const event::ItemEvent &e);

			typedef std::vector<ToggleButton*> ToggleButtonList;

			ToggleButtonList toggleButtonList;

		};
	}
}
#endif