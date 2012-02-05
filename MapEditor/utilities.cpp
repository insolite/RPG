#include "stdafx.h"
#include <windows.h>
#include <vector>

//TODO: ReadDir doesn't work yet
//Error is somewhere in FindFirstFile((LPCWSTR)pathMask, &dat);
int ReadDir(char* path, char** &elements, bool directoriesOnly)
{
	int res, i, count;
	char* pathMask;
	HANDLE elementHandle;
	WIN32_FIND_DATA dat;
	std::vector<std::string> elementsV;

	pathMask = new char[strlen(path) + 3];
	strcpy(pathMask, path);
	strcat(pathMask, "\\*");

	elementHandle = FindFirstFile((LPCWSTR)pathMask, &dat);
	res = FindNextFile(elementHandle, &dat);
	res = FindNextFile(elementHandle, &dat);
	while (res)
	{
		if (directoriesOnly ? dat.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY : 1)
			elementsV.push_back((char*)(dat.cFileName));
		res = FindNextFile(elementHandle, &dat);
	}
	FindClose(elementHandle);
	elements = new char*[elementsV.size()];
	count = elementsV.size();
	for (i = 0; i < count; i++)
	{
		elements[i] = new char[elementsV[i].length() + 1];
		strcpy(elements[i], elementsV[i].c_str());
	}
	delete pathMask;
	elementsV.clear();
	return count;
}

int Str2Int(char *str)
{
	int i, num, decs;
	bool minus;

	i = 0;
	num = 0;
	decs = 1;
	if (str[0] == '-')
		minus = 1;
	else
		minus = 0;
	while (*(str+i) != '\0')
		i++;
	while (--i >= minus)
	{
		num += (*(str + i) - 48) * decs;
		decs *= 10;
	}
	if (str[0] != '-')
		return num;
	else
		return -num;
}

char *Int2Str(int num)
{
	if (!num)
		return "0";
	char* str;
	int len, i, j;

	str = new char[256];
	if (num < 0)
	{
		num =- num;
		j = 1;
		len = 1;
		str[0] = '-';
	}
	else
	{
		j = 0;
		len = 0;
	}
	i = 1;
	while (num / i)
	{
		len++;
		i *= 10;
	}
	while (j < len)
	{
		i = i / 10;
		str[j] = num / i + 48;
		num %= i;
		j++;
	}
	str[j] = '\0';

	return str;
}
