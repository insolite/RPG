#pragma once

class ConnectSocket
{/*
	Socket wrapper.
	Inherited classes:
		ClientSocket
		ServerSocket
		ClientServerSocket
*/
public:
	//WSADATA wsaData;
	SOCKET connectSocket;
	
	__declspec(dllexport) bool Send(char *packet); /*
							 Sends packet to the server. First two bytes defines the length of the packet (without this 2 bytes) as 'short int'.
							 Return value:
							 *	FALSE if successful
							 *	TRUE if error happened
							 */
	__declspec(dllexport) int Receive(char *packet); /*
							   Receives packet from the server. First two bytes defines the length of the packet (without this 2 bytes) as 'short int'.
							   Return value:
							   *	Packet length if successful
							   *	0 if packet was not received
							   *	-1 if 'recv' failed. Usually due to client has been disconnected
							   *	-2 if Packet is too short (less than 2 bytes)
							   *	-3 if announced packet length (in first two bytes, without them) is too big or too short
							   *	-4 if actually received packet length does not match announced
							   */

	__declspec(dllexport) ConnectSocket(void); //Stub
	__declspec(dllexport) ~ConnectSocket(void); //Stub
};
