#pragma once

class NPC :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//NPC(int _id);
	__declspec(dllexport) NPC(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~NPC(void);
};
