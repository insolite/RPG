#pragma once

#define RPGATOR_EET_ELEMENT_DRAGGED 0x10000

class CGUIButton :
	public IGUIButton
{
public:
	bool Dragging;
	core::position2d<s32> DragStart;
	IGUIElement* lastParent;
	rect< s32 > lastPosition;

	__declspec(dllexport) void StartDragging();
	__declspec(dllexport) void StopDragging();

	__declspec(dllexport) CGUIButton(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle, bool noclip = false);
	__declspec(dllexport) ~CGUIButton(void);

	//! called if an event happened.
	__declspec(dllexport) virtual bool OnEvent(const SEvent& event);

	//! draws the element and its children
	__declspec(dllexport) virtual void draw();

	//! sets another skin independent font. if this is set to zero, the button uses the font of the skin.
	__declspec(dllexport) virtual void setOverrideFont(IGUIFont* font=0);

	//! Sets an image which should be displayed on the button when it is in normal state.
	__declspec(dllexport) virtual void setImage(video::ITexture* image=0);

	//! Sets an image which should be displayed on the button when it is in normal state.
	__declspec(dllexport) virtual void setImage(video::ITexture* image, const core::rect<s32>& pos);

	//! Sets an image which should be displayed on the button when it is in pressed state.
	__declspec(dllexport) virtual void setPressedImage(video::ITexture* image=0);

	//! Sets an image which should be displayed on the button when it is in pressed state.
	__declspec(dllexport) virtual void setPressedImage(video::ITexture* image, const core::rect<s32>& pos);

	//! Sets the sprite bank used by the button
	__declspec(dllexport) virtual void setSpriteBank(IGUISpriteBank* bank=0);

	//! Sets the animated sprite for a specific button state
	/** \param index: Number of the sprite within the sprite bank, use -1 for no sprite
	\param state: State of the button to set the sprite for
	\param index: The sprite number from the current sprite bank
	\param color: The color of the sprite
	*/
	__declspec(dllexport) virtual void setSprite(EGUI_BUTTON_STATE state, s32 index,
			video::SColor color=video::SColor(255,255,255,255), bool loop=false);

	//! Sets if the button should behave like a push button. Which means it
	//! can be in two states: Normal or Pressed. With a click on the button,
	//! the user can change the state of the button.
	__declspec(dllexport) virtual void setIsPushButton(bool isPushButton=true);

	//! Checks whether the button is a push button
	__declspec(dllexport) virtual bool isPushButton() const;

	//! Sets the pressed state of the button if this is a pushbutton
	__declspec(dllexport) virtual void setPressed(bool pressed=true);

	//! Returns if the button is currently pressed
	__declspec(dllexport) virtual bool isPressed() const;

	//! Sets if the button should use the skin to draw its border
	__declspec(dllexport) virtual void setDrawBorder(bool border=true);

	//! Checks if the button face and border are being drawn
	__declspec(dllexport) virtual bool isDrawingBorder() const;

	//! Sets if the alpha channel should be used for drawing images on the button (default is false)
	__declspec(dllexport) virtual void setUseAlphaChannel(bool useAlphaChannel=true);

	//! Checks if the alpha channel should be used for drawing images on the button
	__declspec(dllexport) virtual bool isAlphaChannelUsed() const;

	//! Sets if the button should scale the button images to fit
	__declspec(dllexport) virtual void setScaleImage(bool scaleImage=true);

	//! Checks whether the button scales the used images
	__declspec(dllexport) virtual bool isScalingImage() const;

	//! Writes attributes of the element.
	__declspec(dllexport) virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

	//! Reads attributes of the element
	__declspec(dllexport) virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

private:

	struct ButtonSprite
	{
		s32 Index;
		video::SColor Color;
		bool Loop;
	};

	ButtonSprite ButtonSprites[EGBS_COUNT];

	IGUISpriteBank* SpriteBank;
	IGUIFont* OverrideFont;

	video::ITexture* Image;
	video::ITexture* PressedImage;

	core::rect<s32> ImageRect;
	core::rect<s32> PressedImageRect;

	u32 ClickTime;

	bool IsPushButton;
	bool Pressed;
	bool UseAlphaChannel;
	bool DrawBorder;
	bool ScaleImage;
};
