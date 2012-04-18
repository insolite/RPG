#pragma once

class CGUIFileOpenDialog : public IGUIFileOpenDialog
{
public:

	//! constructor
	__declspec(dllexport) CGUIFileOpenDialog(const wchar_t* title, IGUIEnvironment* environment, IGUIElement* parent, s32 id);

	//! destructor
	__declspec(dllexport) virtual ~CGUIFileOpenDialog();

	//! returns the filename of the selected file. Returns NULL, if no file was selected.
	__declspec(dllexport) virtual const wchar_t* getFileName() const;

	//! Returns the directory of the selected file. Returns NULL, if no directory was selected.
	__declspec(dllexport) virtual const io::path& getDirectoryName();

	//! called if an event happened.
	__declspec(dllexport) virtual bool OnEvent(const SEvent& event);

	//! draws the element and its children
	__declspec(dllexport) virtual void draw();

protected:

	//! fills the listbox with files.
	__declspec(dllexport) void fillListBox();

	//! sends the event that the file has been selected.
	__declspec(dllexport) void sendSelectedEvent( EGUI_EVENT_TYPE type );

	//! sends the event that the file choose process has been canceld
	__declspec(dllexport) void sendCancelEvent();

	core::position2d<s32> DragStart;
	core::stringw FileName;
	io::path FileDirectory;

	IGUIButton* CloseButton;
	IGUIButton* OKButton;
	IGUIButton* CancelButton;
	IGUIListBox* FileBox;
	IGUIEditBox* FileNameText;
	IGUIElement* EventParent;
	io::IFileSystem* FileSystem;
	io::IFileList* FileList;
	bool Dragging;

	io::path initialWorkingDirectory;
};
