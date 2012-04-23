#pragma once

//Include

#include "targetver.h"

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wininet.h>

#include "../Include/sqlite3.h"
#include "../Include/Irrlicht/irrlicht.h"
extern "C"
{
	#include "../Include/lua/lua.h"
	#include "../Include/lua/lauxlib.h"
	#include "../Include/lua/lualib.h"
}

#include "../RPGatorDll/RPGatorDll.h"

#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "WinInet.Lib")
#pragma comment(lib, "kernel32.lib")

#pragma comment(lib, "../Lib/sqlite3.lib")
#pragma comment(lib, "../Lib/Irrlicht.lib")
#pragma comment(lib, "../Lib/lua52.lib")

#if _DEBUG
	#pragma comment(lib, "../Debug/RPGator.lib")
#else
	#pragma comment(lib, "../Release/RPGator.lib")
#endif
