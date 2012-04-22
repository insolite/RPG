#include "StdAfx.h"
#include "SqliteResult.h"
#include "Render.h"
#include "GameObject.h"
#include "CurrentGameObject.h"
#include "CGUIButton.h"
#include "IGUIIconTable.h"

IGUIIconTable::IGUIIconTable(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, int width, int height) :
	IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle),
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

	selectedButton = NULL;
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

void IGUIIconTable::addButton(CurrentGameObject<GameObject>* currentGameObject, int id)
{
	addButton(new CGUIButton(Environment, NULL, id, rect< s32 >(0, 0, buttonSize, buttonSize), currentGameObject, false));
}

CGUIButton* IGUIIconTable::getButtonAt(int index)
{
	list<IGUIElement*>::ConstIterator ei = this->getChildren().begin();
	int i = 0;
	while (ei != this->getChildren().end() && i < index)
	{
		ei++;
		i++;
	}
	if ((*ei)->getChildren().getSize() == 1)
	{
		return (CGUIButton*)*(*ei)->getChildren().getLast();
	}
	else
		return NULL;
}

void IGUIIconTable::removeButton(IGUIButton* button, bool shift)
{
	for (list<IGUIElement*>::ConstIterator i = this->getChildren().begin(); i != this->getChildren().end(); i++)
		if ((*i)->getChildren().getSize() == 1)
		{
			if (*(*i)->getChildren().getLast() == button)
			{
				(*i)->removeChild(button);
				if (shift)
				{
					//TODO: shift
				}
				break;
			}
		}
}

//IGUIIconTable::IGUIIconTableContainer

IGUIIconTable::IGUIIconTableContainer::IGUIIconTableContainer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle) :
	IGUIElement(EGUIET_ELEMENT, environment, parent, id, rectangle)
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
