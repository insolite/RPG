// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

class CGUIMeshViewer : public IGUIMeshViewer
{
public:

	//! constructor
	__declspec(dllexport) CGUIMeshViewer(IGUIEnvironment* environment, IGUIElement* parent, s32 id, core::rect<s32> rectangle);

	//! destructor
	__declspec(dllexport) virtual ~CGUIMeshViewer();

	//! sets the mesh to be shown
	__declspec(dllexport) virtual void setMesh(scene::IAnimatedMesh* mesh);

	//! Gets the displayed mesh
	__declspec(dllexport) virtual scene::IAnimatedMesh* getMesh() const;

	//! sets the material
	__declspec(dllexport) virtual void setMaterial(const video::SMaterial& material);

	//! gets the material
	__declspec(dllexport) virtual const video::SMaterial& getMaterial() const;

	//! called if an event happened.
	__declspec(dllexport) virtual bool OnEvent(const SEvent& event);

	//! draws the element and its children
	__declspec(dllexport) virtual void draw();

private:

	video::SMaterial Material;
	scene::IAnimatedMesh* Mesh;
};
