// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

#include "targetver.h"
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <map>
#include <string>
#include <math.h>

//Include

#include "../Include/gl/GL.h"
#include "../Include/gl/GLU.h"
#include "../Include/gl/GLAUX.h"
#include "../Include/SDL/SDL.h"
#include "../Include/SDL/SDL_image.h"
#include "../Include/sqlite3.h"
#include "../Include/Irrlicht/irrlicht.h"

#include "../RPGatorDll/RPGatorDll.h"

//Lib

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "../Lib/opengl32.lib")
#pragma comment(lib, "../Lib/glu32.lib")
#pragma comment(lib, "../Lib/GLAUX.lib")
#pragma comment(lib, "../Lib/SDL.lib")
#pragma comment(lib, "../Lib/SDLmain.lib")
#pragma comment(lib, "../Lib/SDL_image.lib")
#pragma comment(lib, "../Lib/sqlite3.lib")
#pragma comment(lib, "../Lib/Irrlicht.lib")

#pragma comment(lib, "../Debug/RPGator.lib")
