#include "./Scheme.h"

namespace ui
{
	namespace theme
	{
		namespace defaulttheme
		{
			SchemeManager::SchemeManager()
				: scheme(0)
			{
			}

			SchemeManager::~SchemeManager()
			{
			}

			Scheme * SchemeManager::getScheme() const
			{
				assert(scheme);
				return scheme;
			}

			void SchemeManager::setScheme(Scheme *s)
			{
				scheme = s;
			}
		}
	}
}