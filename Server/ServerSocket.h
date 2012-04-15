#pragma once

class ServerSocket :
	public ConnectSocket
{/*
 Holds the server socket
 */
public:
	ServerSocket(char* port); /*
							  Starts the server
							  port: port on which the server will start
							  */
	~ServerSocket(void); //Stops the server
};
