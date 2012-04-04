#pragma once
#include "ServerSocket.h"
#include "ServerClientSocket.h"

enum LogMessageType
{
	Info,
	Warning,
	Error,
	FatalError
};

class Universe
{/*
 Main wrapper. Holds connection socket, game instance, etc.
 */
public:
	static Universe* instance; //Self instance
	ServerSocket* serverSocket; //Server connection socket
	Game* game; //Game instance
	lua_State* luaState;

	void Run(); //Main loop
	void Log(LogMessageType messageType, char* str, ...)
	{
		//Method does not work correctly yet
		va_list params;
		va_start(params, str);
		switch (messageType)
		{
			case Info:
				fprintf(log, "Info: ");
				break;
			case Warning:
				fprintf(log, "Warning: ");
				break;
			case Error:
				fprintf(log, "Error: ");
				break;
			case FatalError:
				fprintf(log, "Fatal error: ");
				break;
		}
		fprintf(log, str, params);
		fputc('\n', log); //fprintf(log, "\n");
		va_end(params);
	}
	
	Universe(void); //Initializes the instance
	~Universe(void); //Finalizes the instance
private:
	FILE* log;
};

