#pragma once
#include "ClientSocket.h"

enum ProgramState
{
	Continue,
	NextLevel,
	Exit
};

enum MenuGUIElements
{
	WindowCloseButton,
	LoginEditBox,
	PasswordEditBox,
	LogInButton,
	RegisterButton,
	RegisterWindow,
	RegisterWindowLoginEditBox,
	RegisterWindowPasswordEditBox,
	RegisterWindowCharacterComboBox,
	CharacterPreviewMeshViewer,
	RegisterWindowOKButton
};

enum ClientGUIElements
{
	ChatBox,
	ChatEditBox,
	ChatInputEditBox,
	InventoryItemsIconTable,
	SkillsIconTable,
	HotkeyBar,
	InventoryToggleButton,
	SkillsToggleButton,
	QuestsToggleButton,
	InventoryWindow,
	SkillsWindow,
	QuestsWindow,
	IconTableItemButton,
	IconTableSkillButton
};

struct HTMLElement
{
	std::string name; //tag name
	std::string content; //tag content
	std::map<std::string, std::string> args; //tag arguments (type="text", src="img.png", etc.)
};

class Universe
{/*
 Main wrapper. Holds connection socket, game instance, etc.
 */
public:
	static Universe* instance; //Self instance
	ClientSocket* connectSocket; //Connection socket to the server
	Game* game; //Current game, that server is running
	CurrentCharacter* currentCharacter; //Current character, attached to the current client
	Location* currentLocation; //Current location of the current character
	bool fullscreen;
	
	//GUI, input
	IGUIEnvironment* guienv;
	MenuEventReceiver* menuEventReceiver;
	ClientEventReceiver* clientEventReceiver;

	char* login; //Buffer between menu and editor
	char* password; //Buffer between menu and editor
	ProgramState state;
	Render* render;
	ICameraSceneNode *camera;
	int cameraY;

	bool Run(); //Main loop
	bool Menu();
	void MenuGUIInit();
	void ClientGUIInit();
	void MenuGUIDestroy();
	void ClientGUIDestroy();
	void DrawScene(); //TEST
	std::vector<HTMLElement> HTML2GUI(char* text);

	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
};
