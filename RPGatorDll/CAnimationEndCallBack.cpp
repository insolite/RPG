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
	/*
	if (node->getType() == ESCENE_NODE_TYPE::ESNT_SHADOW_VOLUME)
	{
		node->remove();
	}
	if (((IAnimatedMeshSceneNode*)node)->getAnimators().size() == 1)
		((IAnimatedMeshSceneNode*)node)->setMD2Animation(EMAT_STAND);
	return;
	*/

	if (node->getID() == 100001) //Magic
		// || node->getType() == ESCENE_NODE_TYPE::ESNT_LIGHT
	{
		node->remove();
	}
	else if (node->getID() == 100002) //Fireball
	{
		node->removeAnimators();
		node->removeAll();
		//node->drop();
		//nod
		//node->remove();
	}
	else if (node->getID() == 100003) //Move
	{
		if (((IAnimatedMeshSceneNode*)node)->getAnimators().size() == 1)
			((IAnimatedMeshSceneNode*)node)->setMD2Animation(EMAT_STAND);
	}
}
