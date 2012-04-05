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

#include "../Include/sqlite3.h"
#include "../Include/Irrlicht/irrlicht.h"

#include "../RPGatorDll/RPGatorDll.h"

//Lib

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "WinInet.Lib")

#pragma comment(lib, "../Lib/sqlite3.lib")
#pragma comment(lib, "../Lib/Irrlicht.lib")

#pragma comment(lib, "../Debug/RPGator.lib")

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;
