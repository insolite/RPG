#include "StdAfx.h"
#include "Render.h"
#include "CGUIButton.h"
#include "IGUIIconTable.h"

IGUIIconTable::IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height) :
	IGUIElement(EGUI_ELEMENT_TYPE::EGUIET_ELEMENT, environment, parent, id, rectangle),
	Dragging(false)
{
	#ifdef _DEBUG
	setDebugName("IGUIIconTable");
	#endif

	this->width = width;
	this->height = height;
	buttonSize = 48;
	int borderWidth = 2;
	int i, j;
	IGUIIconTableContainer* container;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			container = new IGUIIconTableContainer(Environment, this, -1,
				rect< s32 >(j * buttonSize + j * borderWidth,
							i * buttonSize + i * borderWidth,
							j * buttonSize + buttonSize + j * borderWidth,
							i * buttonSize + buttonSize + i * borderWidth)
				);
			this->addChild(container);
		}
}

IGUIIconTable::~IGUIIconTable(void)
{
}

void IGUIIconTable::draw()
{
	core::rect<s32> rect = AbsoluteRect;
	core::rect<s32>* clip = &AbsoluteClippingRect;

	// draw frame
	Environment->getSkin()->draw3DToolBar(this, rect, clip);
	
	IGUIElement::draw();
}

void IGUIIconTable::addButton(CGUIButton* button)
{
	for (list<IGUIElement*>::ConstIterator i = this->getChildren().begin(); i != this->getChildren().end(); i++)
		if ((*i)->getChildren().getSize() == 0)
		{
			(*i)->addChild(button);
			break;
		}
}

void IGUIIconTable::addButton(ITexture* image)
{
	CGUIButton* button = new CGUIButton(Environment, NULL, -1, rect< s32 >(0, 0, buttonSize, buttonSize), false);
	button->setUseAlphaChannel(true);
	if (image)
		button->setImage(image);

	addButton(button);
}

void IGUIIconTable::removeButton(IGUIButton* button)
{
	//TODO: do :)
}

//IGUIIconTable::IGUIIconTableContainer

IGUIIconTable::IGUIIconTableContainer::IGUIIconTableContainer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle) :
	IGUIElement(EGUI_ELEMENT_TYPE::EGUIET_ELEMENT, environment, parent, id, rectangle)
{
	#ifdef _DEBUG
	setDebugName("IGUIIconTableContainer");
	#endif
}

IGUIIconTable::IGUIIconTableContainer::~IGUIIconTableContainer(void)
{
}

void IGUIIconTable::IGUIIconTableContainer::draw()
{
	core::rect<s32> rect = AbsoluteRect;
	core::rect<s32>* clip = &AbsoluteClippingRect;

	// draw frame
	Environment->getSkin()->draw3DToolBar(this, rect, clip);
	
	IGUIElement::draw();
}

void IGUIIconTable::IGUIIconTableContainer::setButton(CGUIButton* button)
{
	if (this->getChildren().getSize() > 0)
		this->removeChild(*this->getChildren().getLast());
	this->addChild(button);
}
