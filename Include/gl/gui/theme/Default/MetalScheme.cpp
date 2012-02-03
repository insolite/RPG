#include "./MetalScheme.h"

#include "../../util/Color.h"
#include "../../util/GradientColor.h"
#include "../../GlyphContext.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			MetalScheme::MetalScheme()
				:	
				defaultBackground(new util::Color(224,224,224)),
				titleBarSelected(new util::GradientColor(util::Color(221,221,236),util::Color(169,169,189),util::GradientColor::DEGREES_90)),
				titleBarDeselected(new util::GradientColor(util::Color(224,224,224),util::Color(180,180,180),util::GradientColor::DEGREES_90)),
				pushableRaisedBackground(new util::GradientColor(util::Color(188,188,188), util::Color(234,234,234),util::GradientColor::DEGREES_180)),
				pushableLoweredBackground(new util::GradientColor(util::Color(148,148,148), util::Color(208,208,208),util::GradientColor::DEGREES_0)),
				textBackground(new util::GradientColor(util::Color(192,192,192),util::Color(255,255,255))),
				textColor(new util::Color(0,0,0)),
				defaultFont(GlyphContext::getInstance().createFont("Vera.ttf",10)),
				menuBarBackground(new util::GradientColor(util::Color(188,188,188), util::Color(234,234,234), util::GradientColor::DEGREES_0)),
				highlight(new util::Color(163,163,182)),
				menuSelectedBackground(new util::GradientColor(util::Color(137,137,155), util::Color(192,192,206),util::GradientColor::DEGREES_0)),
				menuDeselectedBackground(new util::Color(0,0,0,0))

			{
			}

			MetalScheme::~MetalScheme()
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

			util::Paint * MetalScheme::getMenuSelectedBackground() const
			{
				return menuSelectedBackground;
			}

			util::Paint * MetalScheme::getMenuDeselectedBackground() const
			{
				return menuDeselectedBackground;
			}

			util::Paint * MetalScheme::getDefaultBackground() const
			{
				return defaultBackground;
			}

			util::Paint * MetalScheme::getTitleBarSelected() const
			{
				return titleBarSelected;
			}

			util::Paint * MetalScheme::getTitleBarDeselected() const

			{
				return titleBarDeselected;
			}
			
			util::Paint * MetalScheme::getPushableRaisedBackground() const
			{
				return pushableRaisedBackground;
			}
			
			util::Paint * MetalScheme::getPushableLoweredBackground() const
			{
				return pushableLoweredBackground;
			}
			
			util::Paint * MetalScheme::getTextBackground()  const
			{
				return textBackground;
			}
			
			util::Paint * MetalScheme::getTextColor() const
			{
				return textColor;
			}

			Font * MetalScheme::getDefaultFont() const
			{
				return defaultFont;
			}

			util::Paint * MetalScheme::getMenuBarBackground() const
			{
				return menuBarBackground;
			}

			util::Paint * MetalScheme::getHighlight() const
			{
				return highlight;
			}

		}
	}
}