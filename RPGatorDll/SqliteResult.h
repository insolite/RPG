#pragma once

class SqliteResult //TODO: struct
{
public:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> integers;
	std::map<std::string, double> doubles;

	__declspec(dllexport) SqliteResult();
	__declspec(dllexport) ~SqliteResult();
};
