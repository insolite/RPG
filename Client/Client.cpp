#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "Universe.h"

int main(int argc, char* argv[])
{
	Universe* universe;

	universe = new Universe();

	universe->Run();

	return 0;
}
