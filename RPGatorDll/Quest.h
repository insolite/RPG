#pragma once

class Quest :
	public GameObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) Quest(SqliteResult sqliteResult, char* iconPath);
	__declspec(dllexport) ~Quest(void);
};
