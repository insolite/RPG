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

#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include "../Pointers.h"
#include "../util/Dimension.h"

namespace ui
{
	namespace layout
	{
		/**
		* Basic 'interface' for all LayoutManagers.
		* LayoutManagers define and calculate how Components
		* are laid out in a Container.
		*/
		class LayoutManager
		{
		public:
			/**
			* Creates a new LayoutManager.
			*/
			LayoutManager();

			/**
			 * Copy constructor.
			 */
			LayoutManager(const LayoutManager& rhs);

			/**
			 * Assignment operator.
			 */
			LayoutManager& operator=(const LayoutManager& rhs);

			/**
			 * Swaps the contents of a LayoutManager.
			 */
			void swap(LayoutManager& rhs) throw(); 

			/**
			 * Destructor.
			 */
			virtual ~LayoutManager();
			
			/**
			* Returns the vertical spacing between Components.
			*/
			int getVgap() const;

			/**
			* Returns the horizontal spacing between Components.
			*/
			int getHgap() const;

			/**
			* Sets the horizontal spacing between Components.
			*/
			void setHgap(int hGap);

			/**
			* Sets the vertical spacing between Components.
			*/
			void setVgap(int vGap);

			/**
			* Lays out the Components in the given Container.
			* @param
			*	parent The Container which children need to be laid out.
			*/
			virtual void layoutContainer(const Container* parent) {};

			/**
			 * Adds a Component to the LayoutManager with a specific constraint.
			 * @param
			 *	comp Component to be added to the LayoutManager.
			 * @param
			 *	constraint the constraint to use while laying out the Component.
			 */
			virtual void addLayoutComponent(Component* comp, int constraint) {};

			/**
			* Removes the Component from this LayoutManager.
			* @param
			*	comp Component to remove from the LayoutManager.
			*/
			virtual void removeLayoutComponent(Component* comp) {};

			/**
			 * Returns the preferred Dimension the Container likes to
			 * have. This is used to calculate the preferredSize. It
			 * is not guarenteed to be used, but it could happen (one happy customer).
			 * @param
			 *	container Container to calculate and return the preferredSize from.
			 * @return
			 *	The preferred size for the given Container.
			 */
			virtual const util::Dimension  preferredLayoutSize(const Container* parent) const { return util::Dimension(); };
		private:
			int hgap, vgap;
		};
	}
}
#endif