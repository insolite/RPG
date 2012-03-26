#pragma once

class Item :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//Item(int _id);
	__declspec(dllexport) Item(SqliteResult sqliteResult);
	__declspec(dllexport) ~Item(void);
};
