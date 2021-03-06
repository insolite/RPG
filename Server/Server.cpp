// Server.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Universe.h"

typedef unsigned char byte;

int main(int argc, char* argv[])
{
	SetConsoleTitle("Server");
	setlocale(LC_CTYPE, "Russian_Russia.1251");

	Universe* universe;

	universe = new Universe();

	if (argc < 2)
	{
		char gameName[256];
		printf("Please enter the game name\n");
		scanf("%s", gameName);
		universe->Run(gameName);
	}
	else
		universe->Run(argv[1]);

	return 0;
}
