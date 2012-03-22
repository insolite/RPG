#include "stdafx.h"
#include "utilities.h"

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

extern "C" __declspec(dllexport) void SetPacketLength(char* packet, int length)
{
	*((short int*)packet) = length;
}

extern "C" __declspec(dllexport) int GetPacketLength(char* packet)
{
	return *((short int*)packet);
}

extern "C" __declspec(dllexport) void IncreasePacketLength(char* packet, int length)
{
	SetPacketLength(packet, GetPacketLength(packet) + length);
}

extern "C" __declspec(dllexport) void PacketAddString(char* packet, char* str)
{
	strcpy(packet + GetPacketLength(packet) + 2, str);
	IncreasePacketLength(packet, strlen(str) + 1);
}

extern "C" __declspec(dllexport) void SetPacketType(char* packet, char type)
{
	packet[2] = type;
}

extern "C" __declspec(dllexport) int SqliteGetRow(sqlite3* db, char* query, std::map<std::string, std::string> &strings, std::map<std::string, int> &integers)
{
	int result, i, columnsCount;
	sqlite3_stmt *stmt;
	std::string columnName;

	if (sqlite3_prepare(db, query, -1, &stmt, NULL) != SQLITE_OK)
	{
		printf("Couldn't load execute query '%s'\n", query);
		return -1;
	}
	
	while ((result = sqlite3_step(stmt)) != SQLITE_DONE)
	{
		if (result == SQLITE_ROW)
		{
			columnsCount = sqlite3_column_count(stmt);
			for (i = 0; i < columnsCount; i++)
			{
				columnName = sqlite3_column_name(stmt, i);
				switch (sqlite3_column_type(stmt, i))
				{
					case SQLITE_TEXT:
						strings[columnName] = (std::string)(char*)sqlite3_column_text(stmt, i);
						break;
					case SQLITE_INTEGER:
						integers[columnName] = sqlite3_column_int(stmt, i);
						break;
				}
			}
		}
		else
		{
			printf("SQLite error. Code: %d\n", result);
			sqlite3_finalize(stmt);
			return -2;
		}
	}

	sqlite3_finalize(stmt);
	return 1;
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
