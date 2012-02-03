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
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "../CompoundComponent.h"
#include "./Button.h"
#include "./Label.h"
#include "../layout/BorderLayout.h"
#include "../event/MouseListener.h"
#include "../event/MouseEvent.h"

namespace ui
{
	class TitleBar :	public CompoundComponent, public event::MouseAdapter
	{
	public:
		TitleBar(const std::string &label);
		TitleBar(Icon *icon, const std::string &label);

		const std::string & getTitle() const;
		void setTitle(const std::string &title);

		void setIcon(Icon *icon);

		Icon * getIcon() const;

		// *cough*
		Button * getCloseButton();
		Label * getTitleLabel();

		void setActive(bool active);

	private:
		void init();

		Button closeButton;
		Label titleLabel;

		void mousePressed(const event::MouseEvent &e);
		void mouseReleased(const event::MouseEvent &e);

		void mouseDragged(const event::MouseEvent &e);

		layout::BorderLayout layout;

		bool dragging;
		int nextX, nextY;
	};
}

#endif