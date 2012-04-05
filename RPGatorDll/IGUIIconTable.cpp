#include "StdAfx.h"
#include "Render.h"
#include "IGUIIconTable.h"

IGUIIconTable::IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height) :
	IGUIElement(EGUI_ELEMENT_TYPE::EGUIET_ELEMENT, environment, parent, id, rectangle)
{
	#ifdef _DEBUG
	setDebugName("IGUIIconTable");
	#endif

	this->width = width;
	this->height = height;
	buttonSize = 48;
}

IGUIIconTable::~IGUIIconTable(void)
{
}

void IGUIIconTable::draw()
{
	/*
	core::rect<s32> rect = AbsoluteRect;
	core::rect<s32>* clip = &AbsoluteClippingRect;

	// draw frame
	Environment->getSkin()->draw3DToolBar(this, rect, clip);
	*/

	IGUIElement::draw();
}

void IGUIIconTable::addButton(ITexture* image, int localId, const wchar_t* text, const wchar_t* tooltiptext)
{
	int childrenCount;
	int x, y;
	childrenCount = this->getChildren().size();
	x = buttonSize * (childrenCount % width);
	y = buttonSize * (childrenCount / width);
	IGUIButton* btn = Environment->addButton(rect< s32 >(x, y, x + buttonSize, y + buttonSize), this, -1, text, tooltiptext);
	btn->setUseAlphaChannel(true);
	//btn->setScaleImage(true);
	if (image)
		btn->setImage(image);
}

void IGUIIconTable::removeButton(IGUIButton* button)
{
	for (list<IGUIElement*>::ConstIterator i = this->getChildren().begin(); i != this->getChildren().end(); i++)
	{
		//if ((this->getChildren())[i] == button)
		//if (i.Current.Element == button)
		{
			button->remove();
			//TODO: shift elements
			break;
		}
	}
}
