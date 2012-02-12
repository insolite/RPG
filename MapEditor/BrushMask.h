#pragma once

class BrushMask
{
public:
	int width;
	bool** mask;

	void Init(int _width, bool** _mask = NULL);

	BrushMask(void);
	~BrushMask(void);
};
