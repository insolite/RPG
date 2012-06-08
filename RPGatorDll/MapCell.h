#pragma once

class __declspec(dllexport) MapCell :
	public MapObject
{
public:
	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	MapCell(SqliteResult sqliteResult, char* modelPath);
	~MapCell(void);
};
