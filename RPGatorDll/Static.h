#pragma once

class Static :
	public MapObject
{
public:	
	BrushMask* mask;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//Static(int _id);
	__declspec(dllexport) Static(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~Static(void);
};
