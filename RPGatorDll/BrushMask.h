#pragma once

class BrushMask
{
public:
	int width;

	__declspec(dllexport) void Init(int _width, bool** _mask = NULL);
	__declspec(dllexport) bool* operator[](int i)
	{
		return (*(data + i));
	}

	__declspec(dllexport) BrushMask(void);
	__declspec(dllexport) ~BrushMask(void);

//private:
	bool** data;
};
