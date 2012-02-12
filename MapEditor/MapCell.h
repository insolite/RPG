#pragma once
#include "mapobject.h"

enum CellProperty { Free = 0, Locked, Transparment };

class MapCell :
	public MapObject
{
public:
	CellProperty cellProperty;

	MapCell(void);
	~MapCell(void);
};
