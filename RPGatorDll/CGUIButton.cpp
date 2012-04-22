#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"
#include "Render.h"
#include "GameObject.h"
#include "CurrentGameObject.h"
#include "CurrentMapObject.h"
#include "CurrentSkill.h"
#include "CurrentCharacter.h"
#include "ConnectSocket.h"
#include "CGUIButton.h"

CGUIButton::CGUIButton(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, CurrentGameObject<GameObject>* currentGameObject, bool noclip) :
	IGUIButton(environment, parent, id, rectangle),
	SpriteBank(0), OverrideFont(0), Image(0), PressedImage(0),
	ClickTime(0), IsPushButton(false), Pressed(false),
	UseAlphaChannel(false), DrawBorder(true), ScaleImage(false),
	Dragging(false)
{
	#ifdef _DEBUG
	setDebugName("CGUIButton");
	#endif
	setNotClipped(noclip);

	// Initialize the sprites.
	for (u32 i=0; i<EGBS_COUNT; ++i)
		ButtonSprites[i].Index = -1;

	// This element can be tabbed.
	setTabStop(true);
	setTabOrder(-1);

	this->currentGameObject = currentGameObject;

	wchar_t wstr[256];
	mbstowcs(wstr, currentGameObject->base->name, 255);
	this->setToolTipText(wstr);

	this->setUseAlphaChannel(true);
	if (currentGameObject->base->icon)
		this->setImage(currentGameObject->base->icon);
	else
		this->setImage(Render::instance->driver->getTexture("res/rpgator.png"));
}

CGUIButton::~CGUIButton(void)
{
	if (OverrideFont)
		OverrideFont->drop();

	if (Image)
		Image->drop();

	if (PressedImage)
		PressedImage->drop();

	if (SpriteBank)
		SpriteBank->drop();
}


//! Sets if the images should be scaled to fit the button
void CGUIButton::setScaleImage(bool scaleImage)
{
	ScaleImage = scaleImage;
}


//! Returns whether the button scale the used images
bool CGUIButton::isScalingImage() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return ScaleImage;
}


//! Sets if the button should use the skin to draw its border
void CGUIButton::setDrawBorder(bool border)
{
	DrawBorder = border;
}


void CGUIButton::setSpriteBank(IGUISpriteBank* sprites)
{
	if (sprites)
		sprites->grab();

	if (SpriteBank)
		SpriteBank->drop();

	SpriteBank = sprites;
}


void CGUIButton::setSprite(EGUI_BUTTON_STATE state, s32 index, video::SColor color, bool loop)
{
	if (SpriteBank)
	{
		ButtonSprites[(u32)state].Index	= index;
		ButtonSprites[(u32)state].Color	= color;
		ButtonSprites[(u32)state].Loop	= loop;
	}
	else
	{
		ButtonSprites[(u32)state].Index = -1;
	}
}


//! called if an event happened.
bool CGUIButton::OnEvent(const SEvent& event)
{
	if (!IsEnabled)
		return IGUIElement::OnEvent(event);

	switch(event.EventType)
	{
	case EET_KEY_INPUT_EVENT:
		if (event.KeyInput.PressedDown &&
			(event.KeyInput.Key == KEY_RETURN || event.KeyInput.Key == KEY_SPACE))
		{
			if (!IsPushButton)
				setPressed(true);
			else
				setPressed(!Pressed);

			return true;
		}
		if (Pressed && !IsPushButton && event.KeyInput.PressedDown && event.KeyInput.Key == KEY_ESCAPE)
		{
			setPressed(false);
			return true;
		}
		else
		if (!event.KeyInput.PressedDown && Pressed &&
			(event.KeyInput.Key == KEY_RETURN || event.KeyInput.Key == KEY_SPACE))
		{
			//Environment->removeFocus(this);

			if (!IsPushButton)
				setPressed(false);

			if (Parent)
			{
				SEvent newEvent;
				newEvent.EventType = EET_GUI_EVENT;
				newEvent.GUIEvent.Caller = this;
				newEvent.GUIEvent.Element = 0;
				newEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
				Parent->OnEvent(newEvent);
			}
			return true;
		}
		break;
	case EET_GUI_EVENT:
		if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
		{
			if (event.GUIEvent.Caller == this && !IsPushButton)
				setPressed(false);
		}
		break;
	case EET_MOUSE_INPUT_EVENT:
		if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
		{
			if (event.MouseInput.Control)
			{
				DragStart.X = event.MouseInput.X;
				DragStart.Y = event.MouseInput.Y;
				StartDragging();
			}
			else
			{
				if (Environment->hasFocus(this) &&
					!AbsoluteClippingRect.isPointInside(core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y)))
				{
						Environment->removeFocus(this);
						return false;
				}

				if (!IsPushButton)
					setPressed(true);

				Environment->setFocus(this);

				if (Parent)
				{
					Parent->bringToFront(this);
				}
			}
			return true;
		}
		else
		if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
		{
			if (Dragging)
			{
				StopDragging();
			}
			{
				bool wasPressed = Pressed;
				//Environment->removeFocus(this);

				if ( !AbsoluteClippingRect.isPointInside( core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y ) ) )
				{
					if (!IsPushButton)
						setPressed(false);
					return true;
				}

				if (!IsPushButton)
					setPressed(false);
				else
				{
					setPressed(!Pressed);
				}

				if ((!IsPushButton && wasPressed && Parent) ||
					(IsPushButton && wasPressed != Pressed))
				{
					SEvent newEvent;
					newEvent.EventType = EET_GUI_EVENT;
					newEvent.GUIEvent.Caller = this;
					newEvent.GUIEvent.Element = 0;
					newEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
					Parent->OnEvent(newEvent);
				}
			}
			return true;
		}
		else if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
		{
			if (!event.MouseInput.isLeftPressed())
			{
				if (Dragging)
				{
					StopDragging();
				}
			}

			if (Dragging)
			{
				if (Parent &&
					(event.MouseInput.X < Parent->getAbsolutePosition().UpperLeftCorner.X +1 ||
						event.MouseInput.Y < Parent->getAbsolutePosition().UpperLeftCorner.Y +1 ||
						event.MouseInput.X > Parent->getAbsolutePosition().LowerRightCorner.X -1 ||
						event.MouseInput.Y > Parent->getAbsolutePosition().LowerRightCorner.Y -1))
					return true;

				move(core::position2d<s32>(event.MouseInput.X - DragStart.X, event.MouseInput.Y - DragStart.Y));
				DragStart.X = event.MouseInput.X;
				DragStart.Y = event.MouseInput.Y;
				return true;
			}
		}
		break;
	default:
		break;
	}

	return Parent ? Parent->OnEvent(event) : false;
}


//! draws the element and its children
void CGUIButton::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	video::IVideoDriver* driver = Environment->getVideoDriver();

	// todo:	move sprite up and text down if the pressed state has a sprite
	//			draw sprites for focused and mouse-over
	const core::position2di spritePos = AbsoluteRect.getCenter();

	if (!Pressed)
	{
		if (DrawBorder)
			skin->draw3DButtonPaneStandard(this, AbsoluteRect, &AbsoluteClippingRect);

		if (Image)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= ImageRect.getWidth() / 2;
			pos.Y -= ImageRect.getHeight() / 2;

			driver->draw2DImage(Image,
					ScaleImage? AbsoluteRect :
						core::recti(pos, ImageRect.getSize()),
					ImageRect, &AbsoluteClippingRect,
					0, UseAlphaChannel);
		}
		if (SpriteBank && ButtonSprites[EGBS_BUTTON_UP].Index != -1)
		{
			// draw pressed sprite
			SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_UP].Index, spritePos,
				&AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_UP].Color, ClickTime, Render::instance->device->getTimer()->getTime(),
				ButtonSprites[EGBS_BUTTON_UP].Loop, true);
		}
	}
	else
	{
		if (DrawBorder)
			skin->draw3DButtonPanePressed(this, AbsoluteRect, &AbsoluteClippingRect);

		if (PressedImage)
		{
			core::position2d<s32> pos = spritePos;
			pos.X -= PressedImageRect.getWidth() / 2;
			pos.Y -= PressedImageRect.getHeight() / 2;
			// patch by Alan Tyndall/Jonas Petersen
			if (Image == PressedImage && PressedImageRect == ImageRect)
			{
				pos.X += 1;
				pos.Y += 1;
			}
			driver->draw2DImage(PressedImage,
					ScaleImage? AbsoluteRect :
						core::recti(pos, PressedImageRect.getSize()),
					PressedImageRect, &AbsoluteClippingRect,
					0, UseAlphaChannel);
		}

		if (SpriteBank && ButtonSprites[EGBS_BUTTON_DOWN].Index != -1)
		{
			// draw sprite
			SpriteBank->draw2DSprite(ButtonSprites[EGBS_BUTTON_DOWN].Index, spritePos,
				&AbsoluteClippingRect, ButtonSprites[EGBS_BUTTON_DOWN].Color, ClickTime, Render::instance->device->getTimer()->getTime(),
				ButtonSprites[EGBS_BUTTON_DOWN].Loop, true);
		}
	}

	if (Text.size())
	{
		IGUIFont* font = OverrideFont;
		if (!OverrideFont)
			font = skin->getFont(EGDF_BUTTON);

		core::rect<s32> rect = AbsoluteRect;
		if (Pressed)
			rect.UpperLeftCorner.Y += 2;

		if (font)
			font->draw(Text.c_str(), rect,
				skin->getColor(IsEnabled ? EGDC_BUTTON_TEXT : EGDC_GRAY_TEXT),
				true, true, &AbsoluteClippingRect);
	}

	IGUIElement::draw();
}


//! sets another skin independent font. if this is set to zero, the button uses the font of the skin.
void CGUIButton::setOverrideFont(IGUIFont* font)
{
	if (OverrideFont == font)
		return;

	if (OverrideFont)
		OverrideFont->drop();

	OverrideFont = font;

	if (OverrideFont)
		OverrideFont->grab();
}


//! Sets an image which should be displayed on the button when it is in normal state.
void CGUIButton::setImage(video::ITexture* image)
{
	if (image)
		image->grab();
	if (Image)
		Image->drop();

	Image = image;
	if (image)
		ImageRect = core::rect<s32>(core::position2d<s32>(0,0), image->getOriginalSize());

	if (!PressedImage)
		setPressedImage(Image);
}


//! Sets the image which should be displayed on the button when it is in its normal state.
void CGUIButton::setImage(video::ITexture* image, const core::rect<s32>& pos)
{
	setImage(image);
	ImageRect = pos;
}


//! Sets an image which should be displayed on the button when it is in pressed state.
void CGUIButton::setPressedImage(video::ITexture* image)
{
	if (image)
		image->grab();

	if (PressedImage)
		PressedImage->drop();

	PressedImage = image;
	if (image)
		PressedImageRect = core::rect<s32>(core::position2d<s32>(0,0), image->getOriginalSize());
}


//! Sets the image which should be displayed on the button when it is in its pressed state.
void CGUIButton::setPressedImage(video::ITexture* image, const core::rect<s32>& pos)
{
	setPressedImage(image);
	PressedImageRect = pos;
}


//! Sets if the button should behave like a push button. Which means it
//! can be in two states: Normal or Pressed. With a click on the button,
//! the user can change the state of the button.
void CGUIButton::setIsPushButton(bool isPushButton)
{
	IsPushButton = isPushButton;
}


//! Returns if the button is currently pressed
bool CGUIButton::isPressed() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return Pressed;
}


//! Sets the pressed state of the button if this is a pushbutton
void CGUIButton::setPressed(bool pressed)
{
	if (Pressed != pressed)
	{
		ClickTime = Render::instance->device->getTimer()->getTime();
		Pressed = pressed;
	}
}


//! Returns whether the button is a push button
bool CGUIButton::isPushButton() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return IsPushButton;
}


//! Sets if the alpha channel should be used for drawing images on the button (default is false)
void CGUIButton::setUseAlphaChannel(bool useAlphaChannel)
{
	UseAlphaChannel = useAlphaChannel;
}


//! Returns if the alpha channel should be used for drawing images on the button
bool CGUIButton::isAlphaChannelUsed() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return UseAlphaChannel;
}


bool CGUIButton::isDrawingBorder() const
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return DrawBorder;
}


//! Writes attributes of the element.
void CGUIButton::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
{
	IGUIButton::serializeAttributes(out,options);

	out->addBool	("PushButton",		IsPushButton );
	if (IsPushButton)
		out->addBool("Pressed",		Pressed);

	out->addTexture ("Image",		Image);
	out->addRect	("ImageRect",		ImageRect);
	out->addTexture	("PressedImage",	PressedImage);
	out->addRect	("PressedImageRect",	PressedImageRect);

	out->addBool	("UseAlphaChannel",	isAlphaChannelUsed());
	out->addBool	("Border",		isDrawingBorder());
	out->addBool	("ScaleImage",		isScalingImage());

	//   out->addString  ("OverrideFont",	OverrideFont);
}


//! Reads attributes of the element
void CGUIButton::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
{
	IGUIButton::deserializeAttributes(in,options);

	IsPushButton	= in->getAttributeAsBool("PushButton");
	Pressed		= IsPushButton ? in->getAttributeAsBool("Pressed") : false;

	core::rect<s32> rec = in->getAttributeAsRect("ImageRect");
	if (rec.isValid())
		setImage( in->getAttributeAsTexture("Image"), rec);
	else
		setImage( in->getAttributeAsTexture("Image") );

	rec = in->getAttributeAsRect("PressedImageRect");
	if (rec.isValid())
		setPressedImage( in->getAttributeAsTexture("PressedImage"), rec);
	else
		setPressedImage( in->getAttributeAsTexture("PressedImage") );

	setDrawBorder(in->getAttributeAsBool("Border"));
	setUseAlphaChannel(in->getAttributeAsBool("UseAlphaChannel"));
	setScaleImage(in->getAttributeAsBool("ScaleImage"));

	//   setOverrideFont(in->getAttributeAsString("OverrideFont"));

	updateAbsolutePosition();
}

void CGUIButton::StartDragging()
{
	Dragging = true;
	lastParent = getParent();
	lastPosition = this->getRelativePosition();
	Environment->getRootGUIElement()->addChild(this);
	rect< s32 > pos = lastParent->getAbsolutePosition();
	pos.LowerRightCorner = pos.UpperLeftCorner + lastPosition.LowerRightCorner;
	pos.UpperLeftCorner += lastPosition.UpperLeftCorner;
	this->setRelativePosition(pos);
}

void CGUIButton::StopDragging()
{
	Dragging = false;
	vector2d<s32> point = this->getAbsolutePosition().UpperLeftCorner + (this->getRelativePosition().LowerRightCorner - this->getRelativePosition().UpperLeftCorner) / 2;
	
	lastParent->addChild(this);
	lastParent = NULL;
	this->setRelativePosition(lastPosition);

	IGUIElement* dragTarget = Environment->getRootGUIElement()->getElementFromPoint(point);
	SEvent event;
	event.EventType = EET_GUI_EVENT;
	event.GUIEvent.EventType = (irr::gui::EGUI_EVENT_TYPE)RPGATOR_EET_ELEMENT_DRAGGED;
	event.GUIEvent.Caller = this;
	event.GUIEvent.Element = dragTarget; //Can be NULL if we're dragging element not to an GUI element
	//event.MouseInput.X = point.X;
	//event.MouseInput.Y = point.Y;
	Render::instance->device->postEventFromUser(event);
}
