#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;

	universe = new Universe();
	
	while (!universe->Menu())
	{
		if (universe->Run())
			break;
	}

	return 0;
}
