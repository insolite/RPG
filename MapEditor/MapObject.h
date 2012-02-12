#pragma once

class MapObject
{
public:
	char** tags;
	int tagsCount;
	char* name;

	virtual void Abstr ( void ) = 0; //Abstract class

	MapObject(void);
	~MapObject(void);
};
