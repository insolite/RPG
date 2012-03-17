// Client.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;

	universe = new Universe();

	universe->Run();

	return 0;
}
