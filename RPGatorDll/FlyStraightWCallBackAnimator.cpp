#include "stdafx.h"
#include "Render.h"
#include "FlyStraightWCallBackAnimator.h"

//http://code.google.com/p/clancy/source/browse/trunk/clancy_view2/FlyStraightWCallBackAnimator.cpp?r=106

//! constructor
FlyStraightWCallBackAnimator::FlyStraightWCallBackAnimator(const core::vector3df& startPoint,
                                const core::vector3df& endPoint, u32 timeForWay,
                                bool loop, u32 now)
: Start(startPoint), End(endPoint), WayLength(0.0f), TimeFactor(0.0f), StartTime(now), TimeForWay(timeForWay), Loop(loop)
{
        #ifdef _DEBUG
        setDebugName("FlyStraightWCallBackAnimator");
        #endif
        callback = 0;
        onshot = true;
        recalculateImidiateValues();
}


void FlyStraightWCallBackAnimator::recalculateImidiateValues()
{
        Vector = End - Start;
        WayLength = (f32)Vector.getLength();
        Vector.normalize();

        TimeFactor = WayLength / TimeForWay;
}

void FlyStraightWCallBackAnimator::setAnimatorEndCallBack(scene::IAnimationEndCallBack *_callback)
{
        callback = _callback;
}

//! destructor
FlyStraightWCallBackAnimator::~FlyStraightWCallBackAnimator()
{
        callback = NULL;
}

//! animates a scene node
void FlyStraightWCallBackAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
        if (!node)
                return;

        u32 t = (timeMs-StartTime);

        core::vector3df pos = Start;

        if (!Loop && t >= TimeForWay) {
                pos = End;
                //printf("Done %f\n",pos.X);
                node->setPosition(pos);
                
                if (onshot && callback) {
                        onshot = false;
                        callback->OnAnimationEnd((IAnimatedMeshSceneNode *)node);
                }
        }
        else {
                pos += Vector * (f32)fmod((f32)t, (f32)TimeForWay) * TimeFactor;
                //printf("pos %f\n",pos.X);
                node->setPosition(pos);
        }
}

//! Writes attributes of the scene node animator.
void FlyStraightWCallBackAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
        out->addVector3d("Start", Start);
        out->addVector3d("End", End);
        out->addInt("TimeForWay", TimeForWay);
        out->addBool("Loop", Loop);
}


//! Reads attributes of the scene node animator.
void FlyStraightWCallBackAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
        Start = in->getAttributeAsVector3d("Start");
        End = in->getAttributeAsVector3d("End");
        TimeForWay = in->getAttributeAsInt("TimeForWay");
        Loop = in->getAttributeAsBool("Loop");

        recalculateImidiateValues();
}

ISceneNodeAnimator* FlyStraightWCallBackAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
{
        FlyStraightWCallBackAnimator * newAnimator = 
                new FlyStraightWCallBackAnimator(Start, End, TimeForWay, Loop, StartTime);

        return newAnimator;
}
