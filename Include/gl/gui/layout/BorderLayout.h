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

#ifndef BORDERLAYOUT_H
#define BORDERLAYOUT_H

#include "LayoutManager.h"

namespace ui
{
	namespace layout
	{
		/**
		 * Defines a border layout.
		 * A border layout is a layout that has 5 areas, or placeholders,
		 * for Components. These areas can be specified by supplying a constraint.
		 * These constraints should be one of the following:
		 * <ul>
		 *	<li>CENTER - place the Component in the center placeholder</li>
		 *	<li>NORTH - place the Component in the north placeholder</li>
		 *	<li>SOUTH - place the Component in the south placeholder</li>
		 *	<li>EAST - place the Component in the east placeholder</li>
		 *	<li>WEST - place the Component in the west placeholder</li>
		 * </ul>
		 * These directions indicate where the placeholder is located.
		 */
		class BorderLayout : public LayoutManager
		{
		public:
			/**
			 * Lay out the given Container.
			 * @param
			 *	parent the Container to be laid out.
			 */
			void layoutContainer(const Container* parent);

			/**
			 * Add's a component to the LayoutManager with given
			 * constraint. Note that any Component present at the constraints
			 * placeholder will be removed.
			 * @param
			 *	comp Component to add to this LayoutManager.
			 * @param
			 *	constraint Constraint to use while laying out the Components.
			 * @see
			 *	LOCATIONS
			 */
			void addLayoutComponent(Component* comp, int constraint);

			/**
			 * Remove the given Component from the LayoutManager.
			 * @param
			 *	comp the Component to remove from the LayoutManager.
			 */
			void removeLayoutComponent(Component* comp);

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
			 * Default constructor.
			 */
			BorderLayout();

			/**
			 * Copy constructor.
			 */
			BorderLayout(const BorderLayout& rhs);

			/**
			 * Assignment operator.
			 */
			BorderLayout& operator=(const BorderLayout& rhs);

			/**
			 * Swap this LayoutManager with another.
			 */
			void swap(BorderLayout& rhs) throw();

			/**
			 * Create a BorderLayout with given
			 * horizontal and vertical spacing.
			 * @param
			 *	hgap the horizontal spacing between Components.
			 * @param
			 *	vgap the vertical spacing between Components.
			 */
			BorderLayout(int hgap, int vgap);


			BorderLayout(bool fillCorners, int hgap, int vgap);


			BorderLayout(bool fillCorners);


			/**
			 * Defines placeholder locations.
			 */
			enum LOCATIONS
			{
				/**
				 * North position.
				 */
				NORTH,
				/**
				 * South position.
				 */
				SOUTH,

				/**
				 * East position.
				 */
				EAST,

				/**
				 * West position.
				 */
				WEST,

				/**
				 * Center position.
				 */
				CENTER
			};
		private:
			Component *center, *east,*west,*south,*north;
			bool fillCorners;
		};
	}
}

#endif