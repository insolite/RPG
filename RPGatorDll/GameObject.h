#pragma once

class GameObject
{
public:
	int id;
	char name[256];
	char** tags;
	int tagsCount;

	virtual __declspec(dllexport) void Abstr (void) = 0; //Abstract class

	__declspec(dllexport) GameObject(SqliteResult sqliteResult);
	__declspec(dllexport) ~GameObject(void);
};
