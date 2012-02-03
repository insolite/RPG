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

#ifndef DEFAULTTHEME_H
#define DEFAULTTHEME_H



#include "./Theme.h"
#include "./default/FrameTheme.h"
#include "./default/ButtonTheme.h"
#include "./default/ToggleButtonTheme.h"
#include "./default/MenuItemTheme.h"
#include "./default/MenuTheme.h"
#include "./default/MenuBarTheme.h"
#include "./default/PopupMenuTheme.h"
#include "./default/CheckBoxTheme.h"
#include "./default/RadioButtonTheme.h"
#include "./default/LabelTheme.h"
#include "./default/DialogTheme.h"
#include "./default/TitleBarTheme.h"
#include "./default/ProgressBarTheme.h"
#include "./default/TextFieldTheme.h"
#include "./default/SliderTheme.h"
#include "./default/GLCanvasTheme.h"
#include "./default/ScrollbarTheme.h"
#include "./default/ScrollerTheme.h"

#include "./default/Scheme.h"


namespace ui
{
	namespace theme
	{
		class DefaultTheme : public Theme
		{
		public:
			DefaultTheme();
			virtual ~DefaultTheme();
			ThemeComponent * getThemeComponent(const std::string& componentName) const;

		private:
			defaulttheme::FrameTheme *frameTheme;
			defaulttheme::ComponentTheme *componentTheme;
			defaulttheme::ButtonTheme *buttonTheme;
			defaulttheme::ToggleButtonTheme *toggleButtonTheme;
			defaulttheme::MenuItemTheme *menuItemTheme;
			defaulttheme::MenuTheme *menuTheme;
			defaulttheme::MenuBarTheme *menuBarTheme;
			defaulttheme::PopupMenuTheme *popupMenuTheme;
			defaulttheme::CheckBoxTheme *checkBoxTheme;
			defaulttheme::RadioButtonTheme *radioButtonTheme;
			defaulttheme::LabelTheme *labelTheme;
			defaulttheme::DialogTheme *dialogTheme;
			defaulttheme::TitleBarTheme *titleBarTheme;
			defaulttheme::ProgressBarTheme *progressBarTheme;
			defaulttheme::TextFieldTheme *textFieldTheme;
			defaulttheme::SliderTheme *sliderTheme;
			defaulttheme::GLCanvasTheme *glCanvasTheme;
			defaulttheme::ScrollbarTheme *scrollbarTheme;
			defaulttheme::ScrollerTheme *scrollerTheme;

			defaulttheme::Scheme *scheme;
		};
	}
}

#endif