#include "stdafx.h"
#include "Universe.h"
#include "LuaFunctions.h"

int LuaFunctions::SayHello(lua_State* lua)
{
	int n = lua_gettop(lua);
	lua_Number sum = 0;
	if (n < 1)
	{
		lua_pushstring(lua, "Incorrect arguments count");
		lua_error(lua);
		return 1;
	}
	if (!lua_isstring(lua, 1))
	{
		lua_pushstring(lua, "Incorrect argument");
		lua_error(lua);
		return 2;
	}
	printf("Character saying: '%s'\n", lua_tostring(lua, 1));
	return 0;
}
