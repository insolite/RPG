#pragma once

class Item :
	public MapObject
{
public:
	char path[256]; //Predefined path. Just to know path to the script and do not define it each time it executes

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//Item(int _id);
	__declspec(dllexport) Item(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~Item(void);
};
