// MapEditor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include "Universe.h"
#include "Universe.h"



int main(int argc, char* argv[])
{
	(new Universe())->Run();

	return 0;
}

