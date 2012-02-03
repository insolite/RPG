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
#include "./LayoutManager.h"

namespace ui
{
	namespace layout
	{
		LayoutManager::LayoutManager()
			:	hgap(0),
				vgap(0)
		{
		}

		LayoutManager::LayoutManager(const LayoutManager& rhs)
			:	hgap(rhs.hgap),
				vgap(rhs.vgap)
		{
		}

		void LayoutManager::swap(LayoutManager& rhs) throw()
		{
			std::swap(vgap,rhs.vgap);
			std::swap(hgap,rhs.hgap);
		}

		LayoutManager& LayoutManager::operator =(const LayoutManager& rhs)
		{
			LayoutManager temp(rhs);
			swap(temp);
			return *this;
		}

		LayoutManager::~LayoutManager()
		{
		}

		int LayoutManager::getHgap() const
		{
			return hgap;
		}

		int LayoutManager::getVgap() const
		{
			return vgap;
		}

		void LayoutManager::setHgap(int hGap)
		{
			hgap = hGap;
		}

		void LayoutManager::setVgap(int vGap)
		{
			vgap  = vGap;
		}
	}
}