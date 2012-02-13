#pragma once

class BrushMask
{
public:
	int width;

	void Init(int _width, bool** _mask = NULL);
	bool* operator[](int i)
	{
		return (*(data + i));
	}

	BrushMask(void);
	~BrushMask(void);

//private:
	bool** data;
};
