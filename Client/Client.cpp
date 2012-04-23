#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	SetConsoleTitle("Client");
	setlocale(LC_CTYPE, "Russian_Russia.1251");
	
	Universe* universe = new Universe();

	while (!universe->Menu())
	{
		if (universe->Run())
			break;
	}

	return 0;
}
