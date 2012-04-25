#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	//SetConsoleTitle("Client");
	setlocale(LC_CTYPE, "Russian_Russia.1251");
	
	Universe* universe;

	if (argc < 2)
		universe = new Universe("127.0.0.1", "3127");
	else
	{
		universe = new Universe(!strcmp(argv[1], "-s") ? argv[2] : !strcmp(argv[3], "-s") ? argv[4] : "127.0.0.1",
								!strcmp(argv[1], "-p") ? argv[2] : !strcmp(argv[3], "-p") ? argv[4] : "3127"
								);
	}

	
	
	while (!universe->Menu())
	{
		if (universe->Run())
			break;
	}
	
	return 0;
}
