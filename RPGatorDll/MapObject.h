#pragma once

class MapObject :
	public GameObject
{
public:
	IAnimatedMesh* mesh;
	ITexture* texture;

	virtual __declspec(dllexport) void Abstr (void) = 0; //Abstract class

	__declspec(dllexport) MapObject(SqliteResult sqliteResult, char* modelPath);
	__declspec(dllexport) ~MapObject(void);
};
