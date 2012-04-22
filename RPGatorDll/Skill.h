#pragma once

class Skill :
	public GameObject
{
public:
	char scriptPath[256]; //Predefined path. Just to know path to the script and do not define it each time it executes
	core::array< video::ITexture* > effectTextures;

	__declspec(dllexport) void Abstr(void) { }; //Abstract class inheritance

	__declspec(dllexport) Skill(SqliteResult sqliteResult, char* iconPath);
	__declspec(dllexport) ~Skill(void);
};
