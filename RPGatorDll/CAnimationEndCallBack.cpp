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
	if (node->getID() == 5678)// || node->getType() == ESCENE_NODE_TYPE::ESNT_LIGHT
	{
		//node->remove();
		if (((IAnimatedMeshSceneNode*)node)->getAnimators().size() == 1)
			((IAnimatedMeshSceneNode*)node)->setMD2Animation(EMAT_STAND);
	}
	if (node->getID() == 1234)
	{
		//node->remove();
	}
}
