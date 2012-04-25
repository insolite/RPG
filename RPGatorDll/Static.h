#pragma once

class Static :
	public MapObject
{
public:	
	BrushMask* mask;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) void Update();

	__declspec(dllexport) Static(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~Static(void);
};
