#pragma once
#include "MapObject.h"

enum CellProperty { Free = 0, Locked, Transparment };

class MapCell :
	public MapObject
{
public:
	CellProperty cellProperty;

	void Abstr ( void ) { }; //Abstract class inheritance

	MapCell(int _id);
	~MapCell(void);
};
