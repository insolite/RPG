#include "StdAfx.h"
#include "ForwardDeclaration.h"
#include "Render.h"
#include "CGUIMeshViewer.h"

// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

//Following code was changed a little bit by RPGator developers. Now MeshViewer draws mesh considering camera position. Also it does not draw mesh if it is outside of screen

//! constructor
CGUIMeshViewer::CGUIMeshViewer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle)
: IGUIMeshViewer(environment, parent, id, rectangle), Mesh(0)
{
	#ifdef _DEBUG
	setDebugName("CGUIMeshViewer");
	#endif
}


//! destructor
CGUIMeshViewer::~CGUIMeshViewer()
{
	if (Mesh)
		Mesh->drop();
}


//! sets the mesh to be shown
void CGUIMeshViewer::setMesh(scene::IAnimatedMesh* mesh)
{
    if (mesh)
        mesh->grab();
	if (Mesh)
		Mesh->drop();

	Mesh = mesh;

	/* This might be used for proper transformation etc.
	core::vector3df center(0.0f,0.0f,0.0f);
	core::aabbox3d<f32> box;

	box = Mesh->getMesh(0)->getBoundingBox();
	center = (box.MaxEdge + box.MinEdge) / 2;
	*/
}


//! Gets the displayed mesh
scene::IAnimatedMesh* CGUIMeshViewer::getMesh() const
{
	return Mesh;
}


//! sets the material
void CGUIMeshViewer::setMaterial(const video::SMaterial& material)
{
	Material = material;
}


//! gets the material
const video::SMaterial& CGUIMeshViewer::getMaterial() const
{
	return Material;
}


//! called if an event happened.
bool CGUIMeshViewer::OnEvent(const SEvent& event)
{
	return IGUIElement::OnEvent(event);
}


//! draws the element and its children
void CGUIMeshViewer::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	video::IVideoDriver* driver = Environment->getVideoDriver();
	core::rect<s32> viewPort = AbsoluteRect;
	viewPort.LowerRightCorner.X -= 1;
	viewPort.LowerRightCorner.Y -= 1;
	viewPort.UpperLeftCorner.X += 1;
	viewPort.UpperLeftCorner.Y += 1;

	viewPort.clipAgainst(AbsoluteClippingRect);

	// draw the frame

	core::rect<s32> frameRect(AbsoluteRect);
	frameRect.LowerRightCorner.Y = frameRect.UpperLeftCorner.Y + 1;
	skin->draw2DRectangle(this, skin->getColor(EGDC_3D_SHADOW), frameRect, &AbsoluteClippingRect);

	frameRect.LowerRightCorner.Y = AbsoluteRect.LowerRightCorner.Y;
	frameRect.LowerRightCorner.X = frameRect.UpperLeftCorner.X + 1;
	skin->draw2DRectangle(this, skin->getColor(EGDC_3D_SHADOW), frameRect, &AbsoluteClippingRect);

	frameRect = AbsoluteRect;
	frameRect.UpperLeftCorner.X = frameRect.LowerRightCorner.X - 1;
	skin->draw2DRectangle(this, skin->getColor(EGDC_3D_HIGH_LIGHT), frameRect, &AbsoluteClippingRect);

	frameRect = AbsoluteRect;
	frameRect.UpperLeftCorner.Y = AbsoluteRect.LowerRightCorner.Y - 1;
	frameRect.LowerRightCorner.Y = AbsoluteRect.LowerRightCorner.Y;
	skin->draw2DRectangle(this, skin->getColor(EGDC_3D_HIGH_LIGHT), frameRect, &AbsoluteClippingRect);

	// draw the mesh
	
	//begin of changes by CGUIMeshViewer...
	core::rect<s32> oldViewPort = driver->getViewPort();

	if (Mesh
		&& viewPort.LowerRightCorner.X < oldViewPort.getWidth()
		&& viewPort.UpperLeftCorner.X > 0
		&& viewPort.LowerRightCorner.Y < oldViewPort.getHeight()
		&& viewPort.UpperLeftCorner.Y > 0
		)
	{
		//...end of changes by CGUIMeshViewer
		driver->setViewPort(viewPort);

		core::matrix4 mat;
		core::matrix4 mat2;

		//CameraControl->calculateProjectionMatrix(mat);
		//driver->setTransform(video::TS_PROJECTION, mat);

		//begin of changes by CGUIMeshViewer...
		mat.makeIdentity();
		mat2.makeIdentity();
		/*
		f32 rAngle = atan(fabs(Render::instance->Kt.Z - Render::instance->Km.Z) / fabs(Render::instance->Km.Y - Render::instance->Kt.Y));
		rAngle *= 180 / M_PI;
		rAngle -= 45;
		*/
		mat.setRotationDegrees(vector3df(45/* + rAngle*/, 0, 0));
		mat2.setRotationDegrees(vector3df(0, 90, 0));
		mat.setScale(vector3df(4.0f, 1.0f, 1.0f));
		mat *= mat2;

		mat.setTranslation(vector3df(Render::instance->Kt.X,Render::instance->Km.Y - 50.0f,Render::instance->Kt.Z - 5.0f));
		//...end of changes by CGUIMeshViewer
		
		//mat.setror
		//driver->setTransform(video::ETS_VIEW, vector3df(0,Render::instance->Km.Y - 50.0f,0));
		driver->setTransform(video::ETS_WORLD, mat);

		//CameraControl->calculateViewMatrix(mat);
		//driver->setTransform(video::TS_VIEW, mat);

		driver->setMaterial(Material);

		u32 frame = 0;
		if(Mesh->getFrameCount())
			//frame = (os::Timer::getTime()/20)%Mesh->getFrameCount();
			frame = (Render::instance->device->getTimer()->getTime()/20)%Mesh->getFrameCount(); //Changes by CGUIMeshViewer
		const scene::IMesh* const m = Mesh->getMesh(frame);
		for (u32 i=0; i<m->getMeshBufferCount(); ++i)
		{
			scene::IMeshBuffer* mb = m->getMeshBuffer(i);
			driver->drawVertexPrimitiveList(mb->getVertices(),
					mb->getVertexCount(), mb->getIndices(),
					mb->getIndexCount()/ 3, mb->getVertexType(),
					scene::EPT_TRIANGLES, mb->getIndexType());
		}

		driver->setViewPort(oldViewPort);
	}

	IGUIElement::draw();
}
