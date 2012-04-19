#pragma once

class CAnimationEndCallBack :
	public IAnimationEndCallBack
{
public:
	__declspec(dllexport) void OnAnimationEnd(IAnimatedMeshSceneNode * node);

	__declspec(dllexport) CAnimationEndCallBack(void);
	__declspec(dllexport) ~CAnimationEndCallBack(void);
};
