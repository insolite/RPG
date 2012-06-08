// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

class __declspec(dllexport) CGUIMeshViewer : public IGUIMeshViewer
{
public:

	//! constructor
	CGUIMeshViewer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);

	//! destructor
	virtual ~CGUIMeshViewer();

	//! sets the mesh to be shown
	virtual void setMesh(scene::IAnimatedMesh* mesh);

	//! Gets the displayed mesh
	virtual scene::IAnimatedMesh* getMesh() const;

	//! sets the material
	virtual void setMaterial(const video::SMaterial& material);

	//! gets the material
	virtual const video::SMaterial& getMaterial() const;

	//! called if an event happened.
	virtual bool OnEvent(const SEvent& event);

	//! draws the element and its children
	virtual void draw();

private:

	video::SMaterial Material;
	scene::IAnimatedMesh* Mesh;
};
