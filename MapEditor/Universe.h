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

	//Order is critical
	MapCellSelectWindow,
	NPCSelectWindow,
	ItemSelectWindow,
	StaticSelectWindow,
	CharacterSelectWindow,
	MapCellSelectWindowTab,
	NPCSelectWindowTab,
	ItemSelectWindowTab,
	StaticSelectWindowTab,
	CharacterSelectWindowTab,
	MapCellSelectWindowToggleButton,
	NPCSelectWindowToggleButton,
	ItemSelectWindowToggleButton,
	StaticSelectWindowToggleButton,
	CharacterSelectWindowToggleButton,
	MapCellSelectWindowListBox,
	NPCSelectWindowListBox,
	ItemSelectWindowListBox,
	StaticSelectWindowListBox,
	CharacterSelectWindowListBox,
	MapCellSelectWindowOKButton,
	NPCSelectWindowOKButton,
	ItemSelectWindowOKButton,
	StaticSelectWindowOKButton,
	CharacterSelectWindowOKButton,
};

class Universe
{
public:
	static Universe* instance;
	Location* currentLocation;
	Game* game;
	int cameraX, cameraY; //pixels
	int cursorX, cursorY; //points
	int screenWidth, screenHeight; //pixels
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
