#pragma once

class MapObject
{
public:
	char** tags;
	int tagsCount;
	char* name;

	MapObject(void);
	~MapObject(void);
};
