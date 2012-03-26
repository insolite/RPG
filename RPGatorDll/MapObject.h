#pragma once

class MapObject
{
public:
	char** tags;
	int tagsCount;
	int id;
	char* name;

	virtual __declspec(dllexport) void Abstr (void) = 0; //Abstract class

	__declspec(dllexport) MapObject(SqliteResult sqliteResult);
	__declspec(dllexport) ~MapObject(void);
};
