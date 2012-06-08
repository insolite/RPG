#pragma once
#include "utilities.h"

class __declspec(dllexport) SqliteResult //TODO: struct
{
public:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> integers;
	std::map<std::string, f32> doubles;

	SqliteResult();
	~SqliteResult();
};
