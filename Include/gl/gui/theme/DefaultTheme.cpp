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
#include "./DefaultTheme.h"
#include "./default/Scheme.h"

#include "./default/MetalScheme.h"
#include "./default/DefaultScheme.h"

namespace ui
{
	namespace theme
	{
		DefaultTheme::DefaultTheme()
		{
			componentTheme = new defaulttheme::ComponentTheme();
			frameTheme = new defaulttheme::FrameTheme();
			buttonTheme = new defaulttheme::ButtonTheme();
			toggleButtonTheme = new defaulttheme::ToggleButtonTheme();
			menuItemTheme = new defaulttheme::MenuItemTheme();
			menuTheme = new defaulttheme::MenuTheme();
			menuBarTheme = new defaulttheme::MenuBarTheme();
			popupMenuTheme = new defaulttheme::PopupMenuTheme();
			checkBoxTheme = new defaulttheme::CheckBoxTheme();
			radioButtonTheme = new defaulttheme::RadioButtonTheme();
			labelTheme = new defaulttheme::LabelTheme();
			dialogTheme = new defaulttheme::DialogTheme();
			titleBarTheme = new defaulttheme::TitleBarTheme();
			progressBarTheme = new defaulttheme::ProgressBarTheme();
			textFieldTheme = new defaulttheme::TextFieldTheme();
			sliderTheme = new defaulttheme::SliderTheme();
			glCanvasTheme = new defaulttheme::GLCanvasTheme();
			scrollbarTheme = new defaulttheme::ScrollbarTheme();
			scrollerTheme = new defaulttheme::ScrollerTheme();

			scheme = new defaulttheme::DefaultScheme();

			defaulttheme::SchemeManager::getInstance().setScheme(scheme);
		}

		DefaultTheme::~DefaultTheme()
		{
			delete componentTheme;
			delete frameTheme;
			delete buttonTheme;
			delete toggleButtonTheme;
			delete menuItemTheme;
			delete menuTheme;
			delete menuBarTheme;
			delete popupMenuTheme;
			delete checkBoxTheme;
			delete radioButtonTheme;
			delete labelTheme;
			delete dialogTheme;
			delete titleBarTheme;
			delete progressBarTheme;
			delete textFieldTheme;
			delete sliderTheme;
			delete glCanvasTheme;
			delete scrollbarTheme;
			delete scrollerTheme;

			delete scheme;
		}

		ThemeComponent * DefaultTheme::getThemeComponent(const std::string& componentName) const
		{
			if(componentName == "Frame")
			{
				return frameTheme;
			}
			else if(componentName == "Button")
			{
				return buttonTheme;
			}
			else if(componentName == "ToggleButton")
			{
				return toggleButtonTheme;
			}
			else if(componentName == "MenuItem")
			{
				return menuItemTheme;
			}
			else if(componentName == "Menu")
			{
				return menuTheme;
			}
			else if(componentName == "MenuBar")
			{
				return menuBarTheme;
			}
			else if(componentName == "PopupMenu")
			{
				return popupMenuTheme;
			}
			else if(componentName == "CheckBox")
			{
				return checkBoxTheme;
			}
			else if(componentName == "RadioButton")
			{
				return radioButtonTheme;
			}
			else if(componentName == "Label")
			{
				return labelTheme;
			}
			else if(componentName == "Dialog")
			{
				return dialogTheme;
			}
			else if(componentName == "TitleBar")
			{
				return titleBarTheme;
			}
			else if(componentName == "ProgressBar")
			{
				return progressBarTheme;
			}
			else if(componentName == "TextField")
			{
				return textFieldTheme;
			}
			else if(componentName == "Slider")
			{
				return sliderTheme;
			}
			else if(componentName == "GLCanvas")
			{
				return glCanvasTheme;
			}
			else if(componentName == "Scrollbar")
			{
				return scrollbarTheme;
			}
			else if(componentName == "Scroller")
			{
				return scrollerTheme;
			}
			return componentTheme;
		}
	}
}