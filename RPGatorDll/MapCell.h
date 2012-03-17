#pragma once
#include "MapObject.h"

enum CellProperty { Free = 0, Locked, Transparment };

class MapCell :
	public MapObject
{
public:
	CellProperty cellProperty;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	//MapCell(int _id);
	__declspec(dllexport) MapCell(std::map<std::string, std::string> strings, std::map<std::string, int> integers);
	__declspec(dllexport) ~MapCell(void);
};
