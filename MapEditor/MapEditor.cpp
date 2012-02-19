// MapEditor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;
	char* gameName;

	universe = new Universe();

	while (gameName = universe->Menu())
	{
		universe->Run(gameName);
	}

	return 0;
}

