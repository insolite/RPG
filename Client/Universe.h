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
	InventoryWindow,
	InventoryItemsIconTable,
	HotkeyBar,
	TESTSkillUseButton
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
	ICameraSceneNode *camera2;
	int cameraY;

	bool Run(); //Main loop
	bool Menu();
	void MenuGUIInit();
	void ClientGUIInit();
	void MenuGUIDestroy();
	void ClientGUIDestroy();
	void DrawScene(); //TEST

	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
};
