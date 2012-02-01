#include "SpriteBase.h"
#pragma once

class Sprite
{
public:
	SpriteBase* spriteBase;
	long deltaTime;
	int currentFrame;

	void Draw();
    void ToggleAnim();
    void StartAnim();
    void StopAnim();
    void ResetAnim();
    void SetAnim(SpriteBase *base);

	Sprite(void);
	~Sprite(void);
};

