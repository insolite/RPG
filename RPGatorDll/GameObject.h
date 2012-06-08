#pragma once

class __declspec(dllexport) GameObject
{
public:
	int id;
	char name[256];
	char** tags;
	int tagsCount;
	ITexture* icon;

	virtual void Abstr (void) = 0; //Abstract class

	virtual void Update() = 0;

	GameObject(SqliteResult sqliteResult, char* iconPath);
	~GameObject(void);
};
