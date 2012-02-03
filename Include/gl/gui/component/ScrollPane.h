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
#ifndef SCROLLPANE_H
#define SCROLLPANE_H

#include "../Container.h"
#include "./Scrollbar.h"
#include "../layout/BorderLayout.h"
#include "../event/ChangeListener.h"
#include "../event/ChangeEvent.h"

namespace ui
{
	/**
	 * A ScrollPane does not attempt to resize
	 * for accommodating its children, instead
	 * it offers Scrollbars to access them.
	 * ScrollPane is an instance of the Adapter
	 * design pattern, taking its child in the constructor.
	 */
	class ScrollPane : public Container, public ui::event::ChangeListener
	{
	public:
		ScrollPane(Component *comp);

		Scrollbar * getHorizontalScrollbar();
		Scrollbar * getVerticalScrollbar();
	private:
		class ViewContainer : public Container
		{
		public:
			ViewContainer(Component *child);
			void setScrollPane(ScrollPane *parent);
			const util::Dimension & getPreferredSize() const;
			void setHorizontalLocation(float value);
			void setVerticalLocation(float value);
		private:
			void paintChildren(Graphics &g) const;
			Component *view;
			ScrollPane *scrollPane;
		};

		void stateChanged(const event::ChangeEvent &e);
		ViewContainer view;
		Scrollbar horizontalScrollbar;
		Scrollbar verticalScrollbar;
		layout::BorderLayout layout;
		int x,y;
	};
}

#endif