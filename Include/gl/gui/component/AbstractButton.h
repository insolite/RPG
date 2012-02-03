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

#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "../CompoundComponent.h"
#include "../event/KeyListener.h"
#include "../event/KeyEvent.h"

namespace ui
{
	/**
	 * Abstract Button class.
	 * This is an abstract base class for all
	 * button related Components (Buttons,MenuItem).
	 */
	class AbstractButton : public CompoundComponent
	{
	public:
		AbstractButton();
		virtual ~AbstractButton();

		enum PROPERTYCHANGES
		{
			FOCUSPAINTCHANGED = 1,
			SELECTED = 2,
			DESELECTED = 3,
			TEXTCHANGE = 4
		};

		/**
		 * Returns true if the focus is painted,
		 * false otherwise.
		 */
		bool isFocusPainted() const;
		
		/**
		 * Enable or disable focus painting
		 * by setting this flag.
		 */
		void setFocusPainted(bool enable);

		/**
		 * Sets the flag for painting the content area,
		 * that is the background color.
		 */
		void setContentAreaFilled(bool b);

		/**
		 * Returns wether the content area should be painted.
		 */
		bool isContentAreaFilled() const;

		/**
		 * Returns the margin used for laying out the
		 * text.
		 */
		void setMargin(const util::Insets& m);

		/**
		 * Sets the margin used for laying out the text.
		 */
		const util::Insets & getMargin() const;

		/**
		 * Sets the label on the Component.
		 * @param
		 *	value label to be set on the Component
		 */
		void setText(const std::string &value);

		/**
		 * Returns the current label for this Component
		 * @return
		 *	the label.
		 */
		const std::string & getText() const;


		/**
		 * Sets the horizontal alignment of the text.
		 * @param
		 *	alignment See Component globals, can be
		 *	CENTER, LEFT, RIGHT.
		 */
		void setHorizontalAlignment(int alignment);

		/**
		 * Sets the vertical alignment of the text.
		 * @param
		 *	alignment See Component globals, can be
		 *	CENTER, LEFT, RIGHT.
		 */
		void setVerticalAlignment(int alignment);

		/**
		 * Returns the horizontal alignment.
		 */
		int getHorizontalAlignment() const;

		/**
		 * Returns the vertical alignment.
		 */
		int getVerticalAlignment() const;

		/**
		 * Set the Button to its selected state.
		 */
		void setSelected(bool value);

		/**
		 * Returns the selected state of this Button.
		 */
		bool isSelected() const;

		/**
		 * Sets the default Icon.
		 */
		void setDefaultIcon(Icon *icon);

		/**
		 * Sets the selected state Icon.
		 */
		void setSelectedIcon(Icon *icon);

		/**
		 * Sets the disabled default icon for this Button.
		 */
		void setDisabledDefaultIcon(Icon *icon);

		/**
		 * Sets the disabled selected icon for this Button.
		 */
		void setDisabledSelectedIcon(Icon *icon);

		/**
		 * Returns the default icon.
		 */
		Icon * getDefaultIcon() const;

		/**
		 * Returns the disabled default icon.
		 */
		Icon * getDisabledDefaultIcon() const;

		/**
		 * Returns the selected icon.
		 */
		Icon * getSelectedIcon() const;

		/**
		 * Returns the default selected icon.
		 */
		Icon * getDisabledSelectedIcon() const;

		/**
		 * Programmatic click.
		 */
		void doPressed();
		
		/**
		 * Programmatic click.
		 */
		void doReleased();

		/**
		 * Programmatic click.
		 */
		void doClicked();
	private:
		bool focusPainted;
		bool contentAreaPainted;
		bool selected;

		std::string str;
		mutable int horizontalAlignment;
		mutable int verticalAlignment;

		util::Insets margin;

		Icon	*defaultIcon;
		Icon	*selectedIcon;
		Icon	*disabledDefaultIcon;
		Icon	*disabledSelectedIcon;

		class AbstractButtonListener : public ui::event::KeyListener
		{
		public:
			AbstractButtonListener();
			virtual ~AbstractButtonListener();
			void setAbstractButton(AbstractButton *button);
			AbstractButton * getAbstractButton();
			void keyPressed(const event::KeyEvent &e);
			void keyReleased(const event::KeyEvent &e);
			void keyTyped(const event::KeyEvent &e);
		private:
			AbstractButton *parent;
		};

		AbstractButtonListener listener;
	};
}

#endif