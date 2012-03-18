// MapEditor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;
	char* gameName;

	universe = new Universe();

	while (!universe->Menu(gameName))
	{
		universe->Run(gameName);
		delete gameName;
	}

	return 0;
}

