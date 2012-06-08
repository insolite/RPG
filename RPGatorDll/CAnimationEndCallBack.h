#pragma once

class __declspec(dllexport) CAnimationEndCallBack :
	public IAnimationEndCallBack
{
public:
	void OnAnimationEnd(IAnimatedMeshSceneNode * node);

	CAnimationEndCallBack(void);
	~CAnimationEndCallBack(void);
};
