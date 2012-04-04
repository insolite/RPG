#pragma once
#include "ClientSocket.h"

enum ProgramState
{
	Continue,
	NextLevel,
	Exit
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
	int screenWidth, screenHeight; //pixels
	bool fullscreen;
	
	//GUI, input
	IGUIEnvironment* guienv;
	MenuEventReceiver* menuEventReceiver;
	EditorEventReceiver* editorEventReceiver;

	char* gameName; //Buffer between menu and editor
	ProgramState state;
	Render* render;
	ICameraSceneNode *camera;
	ICameraSceneNode *camera2;

	bool Run(); //Main loop
	bool Menu();
	void MenuGUIInit();
	void EditorGUIInit();
	void MenuGUIDestroy();
	void EditorGUIDestroy();

	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
};
