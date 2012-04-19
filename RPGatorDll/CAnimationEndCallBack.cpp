#include "stdafx.h"
#include "Render.h"
#include "CAnimationEndCallBack.h"

CAnimationEndCallBack::CAnimationEndCallBack(void) : IAnimationEndCallBack()
{
}

CAnimationEndCallBack::~CAnimationEndCallBack(void)
{
}

void CAnimationEndCallBack::OnAnimationEnd(IAnimatedMeshSceneNode * node)
{
	if (((IAnimatedMeshSceneNode*)node)->getAnimators().size() == 1)
		((IAnimatedMeshSceneNode*)node)->setMD2Animation(EMAT_STAND);
}
