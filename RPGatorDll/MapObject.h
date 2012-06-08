#pragma once

class __declspec(dllexport) MapObject :
	public GameObject
{
public:
	IAnimatedMesh* mesh;
	ITexture* texture;
	f32 scale;

	virtual void Abstr (void) = 0; //Abstract class

	void ModelInit(char* modelPath);
	void ModelUnLoad();
	
	MapObject(SqliteResult sqliteResult, char* modelPath);
	~MapObject(void);
};
