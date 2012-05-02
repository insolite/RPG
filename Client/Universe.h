#pragma once
#include "ClientSocket.h"

#define CHAT_MAX_LENGTH 4096
#define CHAT_MESSAGE_MAX_LENGTH 256 //Must be less than CHAT_MAX_LENGTH

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
	IconTableSkillButton,

	DialogElement //Must be the last
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
	
	//GUI, input
	IGUIEnvironment* guienv;
	MenuEventReceiver* menuEventReceiver;
	ClientEventReceiver* clientEventReceiver;

	char serverAddress[64];
	char serverPort[8];
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

	Universe(char *serverAddress, char *serverPort); //Initializes the instance
	~Universe(void); //Finalizes the instance
};
