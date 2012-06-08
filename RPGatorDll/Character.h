#pragma once

class __declspec(dllexport) Character :
	public MapObject
{
public:
	f32 speed; //Distanse, that character can pass in one step (e.g. 100ms). It is only the base speed, which means, that it can be modified for each CurrentCharacter, depending of Skills, Buffs, etc.

	void Abstr(void) { }; //Abstract class inheritance

	void Update();

	Character(SqliteResult sqliteResult, char* modelPath);
	~Character(void);
};
