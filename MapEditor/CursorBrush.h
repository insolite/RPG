#pragma once
class CursorBrush
{
public:
	int width;
	bool** mask;

	void Init(int _width, bool** _mask = NULL);

	CursorBrush(void);
	~CursorBrush(void);
};

