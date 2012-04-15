#pragma once

enum ProgramState
{
	Continue,
	NextLevel,
	Exit
};

enum MenuGUIElements
{
	GamesListBox,
	NewGameButton,
	LoadGameButton,
	DeleteGameButton,
	NewGameWindow,
	NewGameOKButton,
	GameNameEditBox,
	DefaultLocationWidthEditBox,
	DefaultLocationHeightEditBox,
	QuitMenuButton
};

enum EditorGUIElements
{
	QuitEditorButton,
	ToolBarWindow,
	FloorsComboBox,
	LocationsComboBox,
	MapObjectsTabControl,
	BrushMaskSizeScroll,
	BrushMaskSizeStaticText,
	LocationsEditButton,
	LocationsEditWindow,
	LocationsEditSaveButton,
	LocationsEditAddButton,
	LocationsEditDeleteButton,
	LocationNameEditBox,
	LocationWidthEditBox,
	LocationHeightEditBox,

	MapObjectEditButton,
	MapObjectAddButton,

	//Select

	MapObjectSelectWindowToggleButton,

	MapCellSelectWindow,
	NPCSelectWindow,
	StaticSelectWindow,
	ItemSelectWindow,
	CharacterSelectWindow,

	MapObjectSelectWindowListBox,
	MapObjectMeshViever,
	MapObjectSelectWindowOKButton,

	//Edit

	MapCellEditWindow,
	NPCEditWindow,
	StaticEditWindow,
	ItemEditWindow,
	CharacterEditWindow,

	MapObjectEditWindowName,
	MapObjectEditWindowTags,
	MapObjectEditWindowPreview,
	MapObjectEditWindowImportModelButton,
	MapObjectEditWindowFileOpenDialog,
	MapObjectEditWindowOKButton,

	//CurrentEdit

	CurrentMapCellEditWindow, //Is not used
	CurrentNPCEditWindow,
	CurrentStaticEditWindow,
	CurrentItemEditWindow,
	CurrentCharacterEditWindow,

	//CurrentMapObjectEditWindowPreview,
	CurrentMapObjectEditWindowOKButton,

	//Add

	MapObjectAddWindowFileOpenDialog
};

class Universe
{
public:
	static Universe* instance;
	Location* currentLocation;
	Game* game;
	int cameraX, cameraY; //pixels
	int cursorX, cursorY; //points
	bool fullscreen;
	int toolbarWidth; //pixels
	int cameraMoveZoneWidth; //pixels
	int toolbarLeftMargin; //pixels
	int brushMaskMinSize; //points
	int brushMaskMaxSize; //points
	char* gameName; //Buffer between menu and editor

	bool** brushMask;
	int brushRadius;

	MapObject* brush[5];
	int brushIndex;

	//GUI, input
	IGUIEnvironment* guienv;
	MenuEventReceiver* menuEventReceiver;
	EditorEventReceiver* editorEventReceiver;

	ProgramState state;

	Render* render;
	ICameraSceneNode *camera;
	ICameraSceneNode *camera2;
	ISceneNode* camPos;

	void CreateBrushMask(int r);
	void DeleteBrushMask();
	void PrintBrushMask();

	void MenuGUIInit();
	void EditorGUIInit();
	void MenuGUIDestroy();
	void EditorGUIDestroy();
	void BrushesInit();
	void SetLocation(Location* location);
	void DrawScene();
	bool Menu();
	bool Run();
	void CameraMove(int x, int y);
	void PaintMapCell();
	
	Universe(void);
	~Universe(void);
};
