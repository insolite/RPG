#pragma once

class Character :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) Character(SqliteResult sqliteResult);
	__declspec(dllexport) ~Character(void);
};
