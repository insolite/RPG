#include "./BasicTheme.h"

namespace ui
{
	namespace theme
	{
		BasicTheme::BasicTheme()
		{
			buttonTheme = new basic::ButtonTheme();
			componentTheme = new basic::BasicComponent();
			menuTheme = new basic::MenuTheme();
			menuItemTheme = new basic::MenuItemTheme();
			popupMenuTheme = new basic::PopupMenuTheme();
			menuBarTheme = new basic::MenuBarTheme();
			toggleButtonTheme = new basic::ToggleButtonTheme();
			radioButtonTheme = new basic::RadioButtonTheme();
			checkBoxTheme = new basic::CheckBoxTheme();
			dialogTheme = new basic::DialogTheme();
			titleBarTheme = new basic::TitleBarTheme();
			labelTheme = new basic::LabelTheme();
			textFieldTheme = new basic::TextFieldTheme();
			sliderTheme = new basic::SliderTheme();
			knobTheme = new basic::KnobTheme();
		}

		BasicTheme::~BasicTheme()
		{
			delete buttonTheme;
			delete componentTheme;
			delete menuTheme;
			delete menuItemTheme;
			delete popupMenuTheme;
			delete menuBarTheme;
			delete toggleButtonTheme;
			delete radioButtonTheme;
			delete checkBoxTheme;
			delete dialogTheme;
			delete titleBarTheme;
			delete labelTheme;
			delete textFieldTheme;
			delete sliderTheme;
			delete knobTheme;
		}

		ThemeComponent * BasicTheme::getThemeComponent(const std::string &componentName) const
		{
			if(componentName == "Button")
			{
				return buttonTheme;
			}
			else if(componentName == "Menu")
			{
				return menuTheme;
			}
			else if(componentName == "MenuItem")
			{
				return menuItemTheme;
			}
			else if(componentName == "PopupMenu")
			{
				return popupMenuTheme;
			}
			else if(componentName == "MenuBar")
			{
				return menuBarTheme;
			}
			else if(componentName == "ToggleButton")
			{
				return toggleButtonTheme;
			}
			else if(componentName == "RadioButton")
			{
				return radioButtonTheme;
			}
			else if(componentName == "CheckBox")
			{
				return checkBoxTheme;
			}
			else if(componentName == "Dialog")
			{
				return dialogTheme;
			}
			else if(componentName == "TitleBar")
			{
				return titleBarTheme;
			}
			else if(componentName == "Label")
			{
				return labelTheme;
			}
			else if(componentName == "TextField")
			{
				return textFieldTheme;
			}
			else if(componentName == "Slider")
			{
				return sliderTheme;
			}
			else if(componentName == "Knob")
			{
				return knobTheme;
			}

			return componentTheme;
		}
	}
}
