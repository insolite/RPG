// Server.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Universe.h"

typedef unsigned char byte;

int main(int argc, char* argv[])
{
	//TEST
	system("color 80");

	Universe* universe;

	universe = new Universe();

	universe->Run();

	return 0;
}
