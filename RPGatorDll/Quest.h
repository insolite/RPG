#pragma once

class __declspec(dllexport) Quest :
	public GameObject
{
public:
	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	Quest(SqliteResult sqliteResult, char* iconPath);
	~Quest(void);
};
