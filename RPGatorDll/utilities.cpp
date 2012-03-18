#include "stdafx.h"

extern "C" __declspec(dllexport) int ReadDir(char* path, char** &elements, bool directoriesOnly)
	/************************************************************************/
	/* Creates array of filenames which are in directory                    */
	/* path: directory to analyze. "dir1/.../dir2" (no '/' in the end)      */
	/* elements: output array for filenames                                 */
	/* directoriesOnly: If 'true' only directories will be counted.         */
	/*                  If 'false' directories and files will be counted    */
	/*                                                                      */
	/* Return value: number of counted elements                             */
	/************************************************************************/
{
	int res, i, count;
	char* pathMask;
	HANDLE elementHandle;
	WIN32_FIND_DATA dat;
	std::vector<std::string> elementsV;

	pathMask = new char[strlen(path) + 3];
	strcpy(pathMask, path);
	strcat(pathMask, "/*");
	
	elementHandle = FindFirstFile(pathMask, &dat); //Project->Properties->Configuration Properties->General->Character Set //MultiByteToWideChar
	res = FindNextFile(elementHandle, &dat); //Skipping '.'
	res = FindNextFile(elementHandle, &dat); //Skipping '..'
	while (res)
	{
		if (directoriesOnly ? dat.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY : 1)
			elementsV.push_back((char*)(dat.cFileName));
		res = FindNextFile(elementHandle, &dat);
	}
	FindClose(elementHandle);
	count = elementsV.size();
	
	elements = new char*[count];
	for (i = 0; i < count; i++)
	{
		elements[i] = new char[elementsV[i].length() + 1];
		strcpy(elements[i], elementsV[i].c_str());
	}
	delete pathMask;
	elementsV.clear();
	return count;
}
/*
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

	str = new char[32];
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
*/
