#pragma once

class Skill :
	public GameObject
{
public:
	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) Skill(SqliteResult sqliteResult);
	__declspec(dllexport) ~Skill(void);
};
