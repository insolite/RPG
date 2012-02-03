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

#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include "../Pointers.h"
#include "./LayoutManager.h"

namespace ui
{
	namespace layout
	{
		/**
		* Grid-like LayoutManager, organizes all
		* components in a grid, with equal width and
		* height.
		* The grids Rectangles (ie 2x2, 4x6) can be set
		* by the user.
		*/
		class GridLayout : public LayoutManager
		{
		public:
			/**
			 * Create a gridlayout with a defined set of
			 * rows and columns.
			 * @param
			 *	rows the number of rows for the grid.
			 * @param
			 *	cols the number of cols for the grid.
			 */
			GridLayout(int rows, int cols);

			/**
		 	 * Create a gridlayout with a defined set of
			 * rows and columns, and given horizontal and
			 * vertical space.
			 * @param
			 *	rows the number of rows for the grid.
			 * @param
			 *	cols the number of cols for the grid.
			 * @param
			 *	vGap vertical space between grid cells.
			 * @param
			 *	hGap horizontal space between grid cells.
			 */
			GridLayout(int rows, int cols, int vGap, int hGap);

			/**
			 * Copy Constructor.
			 * @param
			 *	rhs 
			 */
			GridLayout(const GridLayout& rhs);

			GridLayout& operator=(const GridLayout& rhs);

			void swap(GridLayout& rhs) throw();

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

			/**
			 * Lay out the given Container.
			 * @param
			 *	parent the Container to be laid out.
			 */
			void layoutContainer(const Container* parent);

			/**
			 * Set the number of columns for the grid.
			 * @param
			 *	cols new number of columns.
			 */
			void setColumns(int cols);

			/**
			 * Returns the current number of columns.
			 */
			int getColumns() const;

			/**
			 * Sets the number of rows for the grid.
			 * @param
			 *	rows new number of rows.
			 */
			void setRows(int rows);

			/**
			 * Returns the number of rows.
			 */
			int getRows() const;
		private:
			int rows, cols;
		};
	}
}
#endif