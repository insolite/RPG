// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

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

#include "../Include/gl/GL.h"
#include "../Include/gl/GLU.h"
#include "../Include/gl/GLAUX.h"
#include "../Include/SDL/SDL.h"
#include "../Include/SDL/SDL_image.h"
#include "../Include/sqlite3.h"
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

#pragma comment(lib, "../Lib/opengl32.lib")
#pragma comment(lib, "../Lib/glu32.lib")
#pragma comment(lib, "../Lib/GLAUX.lib")
#pragma comment(lib, "../Lib/SDL.lib")
#pragma comment(lib, "../Lib/SDLmain.lib")
#pragma comment(lib, "../Lib/SDL_image.lib")
#pragma comment(lib, "../Lib/sqlite3.lib")
#pragma comment(lib, "../Lib/lua52.lib")

#pragma comment(lib, "../Debug/RPGator.lib")
