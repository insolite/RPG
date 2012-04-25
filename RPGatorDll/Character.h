#pragma once

class Character :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) void Update();

	__declspec(dllexport) Character(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~Character(void);
};
