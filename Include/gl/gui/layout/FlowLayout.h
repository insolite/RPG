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

#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include "../Pointers.h"
#include "./LayoutManager.h"

namespace ui
{
	namespace layout
	{
		/**
		 * FlowLayout.
		 * A LayoutManager which lays out components
		 * like text. If Components do not fit onto
		 * one line (row), the next Components are moved
		 * to the next line(row).
		 */
		class FlowLayout : public LayoutManager
		{
		public:
			/**
			 * Default Constructor.
			 */
			FlowLayout();

			/**
			 * Copy Constructor.
			 */
			FlowLayout(const FlowLayout& rhs);

			/**
			 * Assignment operator.
			 */
			FlowLayout& operator=(const FlowLayout& rhs);

			/**
			 * Swaps this LayoutManager with another.
			 */
			void swap(FlowLayout& rhs) throw();

			/**
			 * Creates a FlowLayout with given alignment.
			 * @param
			 *	alignment Indicates where the FlowLayout starts, on the left or the right.
			 */
			FlowLayout(int alignment);

			/**
			 * Creates a FlowLayout with given alignment,
			 * horizontal and vertical spacing.
			 * @param
			 *	alignment Indicates where the FlowLayout starts, on the left or the right.
			 * @param
			 *	hgap Horizontal spacing between Components.
			 * @param
			 *	vgap Vertical spacing between Components.
			 */
			FlowLayout(int alignment, int hgap, int vgap);

			/**
			 * Lay out the given Container.
			 * @param
			 *	parent the Container to be laid out.
			 */
			void layoutContainer(const Container* parent);

			/**
			 * Returns the preferred Dimension the Container likes to
			 * have. This is used to calculate the preferredSize. It
			 * is not guarenteed to be used, but it could happen (one happy customer).
			 * @param
			 *	container Container to calculate and return the preferredSize from.
			 * @return
			 *	The preferred size for the given Container.
			 */
			const util::Dimension preferredLayoutSize(const Container* parent) const;
		private:
			void align(ComponentList &row, int rowHeight, util::Insets &parentInsets, util::Dimension &rowDimension, util::Dimension &parentDimension);
			void moveComponents(Container* parent, int x, int y, int width, int height, int rowStart, int rowEnd);
			int alignment;
		};
	}
}
#endif