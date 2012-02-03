#include "./DefaultScheme.h"

#include "../../util/Color.h"
#include "../../util/GradientColor.h"
#include "../../GlyphContext.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			DefaultScheme::DefaultScheme()
				:	
				defaultBackground(new util::Color(224,224,224)),
				titleBarSelected(new util::GradientColor(util::Color(221,221,236),util::Color(139,178,206),util::GradientColor::DEGREES_90)),
				titleBarDeselected(new util::GradientColor(util::Color(224,224,224),util::Color(180,180,180),util::GradientColor::DEGREES_90)),
				pushableRaisedBackground(new util::GradientColor(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_180)),
				pushableLoweredBackground(new util::GradientColor(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0)),
				textBackground(new util::GradientColor(util::Color(192,192,192),util::Color(255,255,255))),
				textColor(new util::Color(0,0,0)),
				defaultFont(GlyphContext::getInstance().createFont("Vera.ttf",10)),
				menuBarBackground(new util::GradientColor(util::Color(188,188,188), util::Color(234,234,234), util::GradientColor::DEGREES_0)),
				highlight(new util::Color(139,178,206)),
				menuSelectedBackground(new util::GradientColor(util::Color(103,132,153), util::Color(127,163,188),util::GradientColor::DEGREES_0)),
				menuDeselectedBackground(new util::Color(0,0,0,0))

			{
			}

			DefaultScheme::~DefaultScheme()
			{
				delete defaultBackground;
				delete titleBarSelected;
				delete titleBarDeselected;
				delete pushableRaisedBackground;
				delete pushableLoweredBackground;
				delete textBackground;
				delete textColor;
				delete menuBarBackground;
				delete highlight;
				delete menuSelectedBackground;
				delete menuDeselectedBackground;
			//	delete defaultFont;
			}

			util::Paint * DefaultScheme::getMenuSelectedBackground() const
			{
				return menuSelectedBackground;
			}

			util::Paint * DefaultScheme::getMenuDeselectedBackground() const
			{
				return menuDeselectedBackground;
			}

			util::Paint * DefaultScheme::getDefaultBackground() const
			{
				return defaultBackground;
			}

			util::Paint * DefaultScheme::getTitleBarSelected() const
			{
				return titleBarSelected;
			}

			util::Paint * DefaultScheme::getTitleBarDeselected() const

			{
				return titleBarDeselected;
			}
			
			util::Paint * DefaultScheme::getPushableRaisedBackground() const
			{
				return pushableRaisedBackground;
			}
			
			util::Paint * DefaultScheme::getPushableLoweredBackground() const
			{
				return pushableLoweredBackground;
			}
			
			util::Paint * DefaultScheme::getTextBackground()  const
			{
				return textBackground;
			}
			
			util::Paint * DefaultScheme::getTextColor() const
			{
				return textColor;
			}

			Font * DefaultScheme::getDefaultFont() const
			{
				return defaultFont;
			}

			util::Paint * DefaultScheme::getMenuBarBackground() const
			{
				return menuBarBackground;
			}

			util::Paint * DefaultScheme::getHighlight() const
			{
				return highlight;
			}

		}
	}
}