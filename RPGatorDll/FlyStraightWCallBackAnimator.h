#pragma once

//http://code.google.com/p/clancy/source/browse/trunk/clancy_view2/FlyStraightWCallBackAnimator.h?r=106

class FlyStraightWCallBackAnimator : public ISceneNodeAnimator
{
public:

        //! constructor
        FlyStraightWCallBackAnimator(const core::vector3df& startPoint,
                                        const core::vector3df& endPoint,
                                        u32 timeForWay,
                                        bool loop, u32 now);

        //! destructor
        virtual ~FlyStraightWCallBackAnimator();

        //! animates a scene node
        virtual void animateNode(ISceneNode* node, u32 timeMs);

        void setAnimatorEndCallBack(IAnimationEndCallBack *_callback=0);

        //! Writes attributes of the scene node animator.
        virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

        //! Reads attributes of the scene node animator.
        virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

        //! Returns type of the scene node animator
        virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_FLY_STRAIGHT; }
                
        //! Creates a clone of this animator.
        /** Please note that you will have to drop
        (IReferenceCounted::drop()) the returned pointer after calling
        this. */
        virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);


public:

        void recalculateImidiateValues();
        scene::IAnimationEndCallBack * callback;
        core::vector3df Start;
        core::vector3df End;
        core::vector3df Vector;
        bool onshot;
        f32 WayLength;
        f32 TimeFactor;
        u32 StartTime;
        u32 TimeForWay;
        bool Loop;
};
