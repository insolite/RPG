#pragma once

class SqliteResult //TODO: struct
{
public:
	std::map<std::string, std::string> strings;
	std::map<std::string, int> integers;

	__declspec(dllexport) SqliteResult();
	__declspec(dllexport) ~SqliteResult();
};
