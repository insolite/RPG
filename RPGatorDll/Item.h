#pragma once

class __declspec(dllexport) Item :
	public MapObject
{
public:
	char path[256]; //Predefined path. Just to know path to the script and do not define it each time it executes

	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	Item(SqliteResult sqliteResult, char* modelPath);
	~Item(void);
};
