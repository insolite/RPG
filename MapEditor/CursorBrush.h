#pragma once
class CursorBrush
{
public:
	int width;
	bool** mask;

	CursorBrush(int id);
	~CursorBrush(void);
};

