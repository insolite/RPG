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
#ifndef TEXTUTIL_H
#define TEXTUTIL_H

#include "../Pointers.h"
#include "../component/AbstractButton.h"

namespace ui
{
	namespace theme
	{
		typedef std::vector<std::string> StringBuffer;
		typedef std::pair<std::string,util::Dimension> StringInfo;
		typedef std::vector<StringInfo> StringInfoBuffer;

		class TextWrappingAlgorithm
		{
		public:
			virtual StringInfoBuffer wrapText(const std::string &text, Font *font, int width) const = 0;
			virtual ~TextWrappingAlgorithm() {};
		};

		class CuttoffAlgorithm : public TextWrappingAlgorithm
		{
		public:
			StringInfoBuffer wrapText(const std::string &text, Font *font, int width) const;
			virtual ~CuttoffAlgorithm() {};
		};

		class TextUtil
		{
		public:
				
				StringInfoBuffer getButtonString(const util::Dimension &boundingBox, const util::Insets &margin, Font *font, const std::string &text, bool wordWrap) const;
				StringInfoBuffer getButtonString(Font *font, const std::string &text) const;
				std::string getMaxString(const std::string &str, Font *font, int maxWidth) const;
				util::Point getTextAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, const StringInfoBuffer &buffer) const;
				util::Point getIconAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, Icon *icon) const;
				util::Point getContentAlignment(const util::Dimension &boundingBox, const util::Insets &margin, const util::Insets &insets, int horizontalAlignment, int verticalAlignment, const util::Dimension &contentBoundingBox) const;
				util::Dimension getBufferBoundingBox(const StringInfoBuffer &buffer) const;
				void paintButtonFocus(int x, int y, Graphics &g, const StringInfoBuffer &buffer, int spacing, Icon *icon) const;
				void paintButton(int x, int y, Graphics &g, const StringInfoBuffer &buffer, int alignment, Icon *icon) const;
				//util::Dimension getContentBoundingBox(const util::Dimension &bufferBoundingBox, Icon *icon, const util::Insets &margin, const util::Insets &insets);
				util::Dimension getContentBoundingBox(const util::Dimension &bufferBoundingBox, Icon *icon) const;
		public:
			TextUtil(TextWrappingAlgorithm *algorithm);
			StringInfoBuffer fitStringInBoundingBox(const std::string &text, const util::Dimension &componentBoundingBox, const util::Dimension &iconBoundingBox, Font *font, const util::Insets &componentInsets, const util::Insets &componentMargins) const;
			util::Dimension getStringBoundingBox(const StringInfoBuffer &str) const;
			util::Dimension getIconBoundingBox(Icon *icon) const;
			util::Dimension getPreferredBoundingBox(const std::string &text, Icon *icon, Font *font) const;
			int getVerticalAlignment(const util::Dimension &contentBoundingBox, const util::Dimension &componentBoundingBox, int alignment, const util::Insets &componentInsets, const util::Insets &componentMargins) const;
			int getHorizontalAlignment(const util::Dimension &textBoundingBox, const util::Dimension &iconBoundingBox, const util::Dimension &componentBoundingBox, int alignment, const util::Insets &componentInsets, const util::Insets &componentMargins) const;
		private:
			TextWrappingAlgorithm *textWrappingAlgorithm;
			StringBuffer splitText(const std::string &text) const;
		};

		class TextPainter
		{
		public:

		};
	}
}
#endif