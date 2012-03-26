#pragma once

enum CellProperty { Free = 0, Locked, Transparment };

class MapCell :
	public MapObject
{
public:
	CellProperty cellProperty;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//MapCell(int _id);
	__declspec(dllexport) MapCell(SqliteResult sqliteResult);
	__declspec(dllexport) ~MapCell(void);
};
