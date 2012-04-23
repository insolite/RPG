#pragma once

enum CellProperty { Free = 0, Locked, Transparment };

class MapCell :
	public MapObject
{
public:
	CellProperty cellProperty;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) void Update();

	__declspec(dllexport) MapCell(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~MapCell(void);
};
