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
#include "./ButtonGroup.h"

namespace ui
{
	namespace util
	{
		void ButtonGroup::add(ToggleButton* button)
		{
			assert(button);

			button->addItemListener(this);
			
			if(button->isSelected())
			{
				ToggleButtonList::const_iterator iter;
				for(iter = toggleButtonList.begin(); iter != toggleButtonList.end(); ++iter)
				{
					(*iter)->setSelected(false);
				}
			}
			toggleButtonList.push_back(button);
		}

		void ButtonGroup::remove(ToggleButton* button)
		{
			assert(button);

			ToggleButtonList::iterator iter = std::find(toggleButtonList.begin(),toggleButtonList.end(),button);

			if(iter != toggleButtonList.end())
			{
				(*iter)->removeItemListener(this);
				toggleButtonList.erase(iter);
			}
		}

		void ButtonGroup::itemStateChanged(const event::ItemEvent &e)
		{
			if(e.getID() == event::ItemEvent::SELECTED)
			{
				ToggleButtonList::const_iterator iter;
				for(iter = toggleButtonList.begin(); iter != toggleButtonList.end(); ++iter)
				{
					if((*iter) != e.getSource())
					{
						(*iter)->setSelected(false);
					}
				}
			}
			else if(e.getID() == event::ItemEvent::DESELECTED)
			{
				ToggleButtonList::const_iterator iter;
				for(iter = toggleButtonList.begin(); iter != toggleButtonList.end(); ++iter)
				{
					if((*iter) == e.getSource())
					{
						(*iter)->setSelected(true);
					}
				}
			}
		}

		int ButtonGroup::getButtonCount()
		{
			return static_cast<int>(toggleButtonList.size());
		}
	}
}
