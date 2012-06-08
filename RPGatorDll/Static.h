#pragma once

class __declspec(dllexport) Static :
	public MapObject
{
public:	
	BrushMask* mask;

	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	Static(SqliteResult sqliteResult, char* modelPath);
	~Static(void);
};
