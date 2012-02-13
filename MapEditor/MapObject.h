#pragma once

class MapObject
{
public:
	char** tags;
	int tagsCount;
	int id;
	char* name;

	virtual void Abstr ( void ) = 0; //Abstract class

	MapObject(void);
	~MapObject(void);
};
