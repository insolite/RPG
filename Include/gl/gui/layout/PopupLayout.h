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

#ifndef POPUPLAYOUT_H
#define POPUPLAYOUT_H

#include "./LayoutManager.h"

namespace ui
{
	namespace layout
	{
		/**
		* Special layout manager for popups that are owned
		* by other Components (such as a Menu). This calculates
		* the preferredSize for the Component based on it's children
		* and sets it, regardless of the parents bounds.
		* This way we can make maximal use of the Component hierarchy,
		* without specific hacks (except this one :).
		*/
		class PopupLayout : public LayoutManager
		{
		public:
			/**
			 * Does the layout for the given Container.
			 * this is done by setting the Containers first
			 * child (which should be the Popup) to it's preferred
			 * size.
			 * @param
			 *	parent Container to be laid out.
			 */
			void layoutContainer(const Container* parent);

			/**
			 * Not used.
			 * @param
			 *	comp Component to add to the LayoutManager.
			 * @param
			 *	constraint Constraint to use.
			 */
			void addLayoutComponent(Component* comp, int constraint);

			/**
			 * Not used.
			 * @param
			 *	comp the Component to be removed from the LayoutManager.
			 */
			void removeLayoutComponent(Component* comp);

			/**
			 * Returns the preferredSize of this Container.
			 * It returns the parents bounds, just as getPreferredSize would
			 * do if we have no layout. Simple, effective.
			 * @param
			 *	container Container to calculate and return the preferredSize from.
			 * @return
			 *	The preferred size for the given Container.
			 */
			const util::Dimension preferredLayoutSize(const Container* parent) const;
		};
	}
}
#endif