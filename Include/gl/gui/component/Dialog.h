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
#ifndef DIALOG_H
#define DIALOG_H

#include "./Window.h"
#include "../Icon.h"
#include "./TitleBar.h"
#include "../event/MouseListener.h"
#include "../event/MouseEvent.h"
#include "../event/PropertyEvent.h"
#include "../event/PropertyListener.h"

namespace ui
{
	/**
	 * A dialog window.
	 * Dialog has a TitleBar with an exitbutton.
	 * No minimize or maximize buttons are supplied.
	 */
	class Dialog : public Window , public event::PropertyListener //, public event::MouseAdapter
	{
	public:
		/**
		 * Returns the title of the Dialog.
		 */
		const std::string &getTitle() const;

		/**
		 * Set the title on the Dialog.
		 */
		void setTitle(const std::string &title);

		/**
		 * Returns the Icon of this Dialog.
		 */
		const Icon * getIcon() const;

		/**
		 * Sets the Icon for this Dialog.
		 */
		void setIcon(Icon * icon);

		/**
		 * Sets to owner of this Dialog.
		 */
		void setOwner(Window *owner);

		/**
		 * Returns the owner of this Dialog.
		 */
		const Window * getOwner() const;

		/**
		 * Create a new Dialog with given owner and title.
		 * @param
		 * owner Window derivative that owns this Dialog.
		 * @param 
		 * title Title used for the dialog.
		 */
		Dialog(Window *owner, const std::string &title);

		/**
		 * Create a new Dialog with given owner and title.
		 * @param
		 * owner Window derivative that owns this Dialog.
		 * @param 
		 * title Title used for the dialog.
		 */
		Dialog(Window *owner, Icon *icon, const std::string &title);

		enum PROPERTYCHANGE
		{
			OWNERCHANGE = 5,
			TITLECHANGE = 6,
			ICONCHANGE = 7,
			ACTIVECHANGE = 8,
			CLOSE_RELEASED = 9
		};

	private:
		void init(Window *o);
		Window *owner;
		TitleBar titleBar;

		class DialogListener : public event::MouseAdapter
		{
		public:
			DialogListener();
			~DialogListener();
			void setParent(Dialog *d);
			Dialog * getParent() const;
		private:
			void mouseReleased(const event::MouseEvent &e);
			void mousePressed(const event::MouseEvent &e);
		//	void mouseReleased(const event::MouseEvent &e);
			void mouseDragged(const event::MouseEvent &e);
			Dialog *parent;
			bool resizing;
		};

		void propertyChanged(const event::PropertyEvent &e);
		
		DialogListener listener;
		

	};
}

#endif