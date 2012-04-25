#pragma once

class MapCell :
	public MapObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) void Update();

	__declspec(dllexport) MapCell(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~MapCell(void);
};
