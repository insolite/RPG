#include "StdAfx.h"
#include "Render.h"
#include "CGUIEditBox.h"
#include "IGUIChatBox.h"

IGUIChatBox::IGUIChatBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id, s32 editBoxId, s32 chatInpuId, core::rect<s32> rectangle) :
	IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle)
{
	rect<s32> internatRect = rectangle;
	internatRect.LowerRightCorner -= internatRect.UpperLeftCorner;
	internatRect.UpperLeftCorner -= internatRect.UpperLeftCorner; // = vector2d<s32>(0, 0);

	rect<s32> chatEditBoxRect = internatRect;
	chatEditBoxRect.LowerRightCorner.Y -= 24;
	CGUIEditBox* chatEditBox = new CGUIEditBox(NULL, true, environment, this, editBoxId, chatEditBoxRect);
	chatEditBox->setOverrideColor(SColor(223, 255, 255, 255));
	chatEditBox->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	chatEditBox->setMultiLine(true);
	chatEditBox->setEditable(false);
	chatEditBox->setWordWrap(true);
	chatEditBox->drop();

	rect<s32> chatInputEditBoxRect = internatRect;
	chatInputEditBoxRect.UpperLeftCorner.Y = chatInputEditBoxRect.LowerRightCorner.Y - 24 - 4;
	CGUIEditBox* chatInputEditBox = new CGUIEditBox(NULL, true, environment, this, chatInpuId, chatInputEditBoxRect);
	chatInputEditBox->setOverrideColor(SColor(223, 255, 255, 255));
	chatInputEditBox->drop();
}

IGUIChatBox::~IGUIChatBox(void)
{
}

void IGUIChatBox::draw()
{
	IGUIElement::draw();
}
