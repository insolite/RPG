#pragma once

class __declspec(dllexport) Skill :
	public GameObject
{
public:
	char scriptPath[256]; //Predefined path. Just to know path to the script and do not define it each time it executes
	core::array< video::ITexture* > effectTextures;

	int useDelay;

	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	Skill(SqliteResult sqliteResult, char* iconPath);
	~Skill(void);
};
