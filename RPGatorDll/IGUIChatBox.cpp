#include "StdAfx.h"
#include "Render.h"
#include "CGUIEditBox.h"
#include "IGUIChatBox.h"

IGUIChatBox::IGUIChatBox(IGUIEnvironment* environment, IGUIElement* parent, s32 id, s32 editBoxId, s32 chatInpuId, core::rect<s32> rectangle) :
	IGUIElement(EGUI_ELEMENT_TYPE::EGUIET_ELEMENT, environment, parent, id, rectangle)
{
	//IGUIEditBox* chatEditBox = Environment->addEditBox(NULL, rect< s32 >(0, 0, 256, 256), true, this, editBoxId);
	CGUIEditBox* chatEditBox = new CGUIEditBox(NULL, true, environment, this, editBoxId, rect< s32 >(0, 0, 256, 256));
	chatEditBox->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_LOWERRIGHT);
	chatEditBox->setMultiLine(true);
	//chatEditBox->setEditable(false);
	//Environment->addEditBox(NULL, rect< s32 >(0, 256, 256, 256 + 24), true, this, chatInpuId);
	CGUIEditBox* chatInputEditBox = new CGUIEditBox(NULL, true, environment, this, chatInpuId, rect< s32 >(0, 256 - 4, 256, 256 + 24 + 4));

	chatEditBox->setOverrideColor(SColor(223, 255, 255, 255));
	chatInputEditBox->setOverrideColor(SColor(223, 255, 255, 255));
}

IGUIChatBox::~IGUIChatBox(void)
{
}

void IGUIChatBox::draw()
{
	IGUIElement::draw();
}
