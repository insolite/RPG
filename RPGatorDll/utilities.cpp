#include "stdafx.h"
#include "ForwardDeclaration.h"
#include "SqliteResult.h"
#include "utilities.h"

extern "C" __declspec(dllexport) int ReadDir(const char* path, char** &elements, bool directoriesOnly)
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

extern "C" __declspec(dllexport) void ClearDir(const char* path)
{
	char** paths;
	int i;

	int numOfDirs = ReadDir(path, paths, true);

	if (numOfDirs != 0)
	{
		for (i = 0; i < numOfDirs; i++)
		{
			ClearDir( ((std::string)path + "/" + (std::string)paths[i]).c_str() );
			printf("Deleting directory: %s\n", paths[i]);
			RemoveDirectory(((std::string)path + "/" + (std::string)paths[i]).c_str());
			delete paths[i];
		}
	}

	delete paths;
	int numOfFiles = ReadDir(path, paths, false);

	if (numOfFiles != 0)
	{
		for (i = 0; i < numOfFiles; i++)
		{
			printf("Deleting file: %s\n",paths[i]);
			DeleteFile(((std::string)path + "/" + (std::string)paths[i]).c_str());
		}
	}
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

extern "C" __declspec(dllexport) void PacketAddInt(char* packet, int n)
{
	memcpy(packet + GetPacketLength(packet) + 2, (char*)&n, 4);
	IncreasePacketLength(packet, 4);
}

extern "C" __declspec(dllexport) void PacketAddShortInt(char* packet, short int n)
{
	memcpy(packet + GetPacketLength(packet) + 2, (char*)&n, 2);
	IncreasePacketLength(packet, 2);
}

extern "C" __declspec(dllexport) void PacketAddByte(char* packet, char n)
{
	packet[GetPacketLength(packet) + 2] = n;
	IncreasePacketLength(packet, 1);
}

extern "C" __declspec(dllexport) char* PacketGetString(char* packet, int pos)
{
	return packet + 2 + pos;
}

extern "C" __declspec(dllexport) int PacketGetInt(char* packet, int pos)
{
	return *((int*)(packet + 2 + pos));
}

extern "C" __declspec(dllexport) short int PacketGetShortInt(char* packet, int pos)
{
	return *((short int*)(packet + 2 + pos));
}

extern "C" __declspec(dllexport) char PacketGetByte(char* packet, int pos)
{
	return packet[2 + pos];
}

extern "C" __declspec(dllexport) void SetPacketType(char* packet, Packet type)
{
	packet[2] = type;
}

extern "C" __declspec(dllexport) Packet GetPacketType(char* packet)
{
	return (Packet)packet[2];
}

extern "C++" __declspec(dllexport) std::vector<SqliteResult> SqliteGetRows(sqlite3* db, char* query)
{
	int result, i, columnsCount, rowsCount;
	sqlite3_stmt *stmt;
	std::string columnName;
	std::vector<SqliteResult> sqliteResults;

	if (sqlite3_prepare(db, query, -1, &stmt, NULL) != SQLITE_OK)
	{
		printf("Couldn't execute query '%s'\n", query);
		return sqliteResults;
	}
	
	rowsCount = 0;
	while ((result = sqlite3_step(stmt)) != SQLITE_DONE)
	{
		if (result == SQLITE_ROW)
		{
			sqliteResults.push_back(SqliteResult());
			
			columnsCount = sqlite3_column_count(stmt);
			for (i = 0; i < columnsCount; i++)
			{
				columnName = sqlite3_column_name(stmt, i);
				switch (sqlite3_column_type(stmt, i))
				{
					case SQLITE_TEXT:
						sqliteResults[rowsCount].strings[columnName] = (std::string)(char*)sqlite3_column_text(stmt, i);
						break;
					case SQLITE_INTEGER:
						sqliteResults[rowsCount].integers[columnName] = sqlite3_column_int(stmt, i);
						break;
				}
			}
			rowsCount++;
		}
		else
		{
			printf("SQLite error. Code: %d\n", result);
			sqlite3_finalize(stmt);
			return sqliteResults;
		}
	}
	sqlite3_finalize(stmt);

	return sqliteResults;
}

int Pix2Index(int pos)
{
	return pos / CELL_SIZE;
}

int Index2Pix(int pos)
{
	return pos * CELL_SIZE;
}

int PixRound(int pos)
{
	return Index2Pix(Pix2Index(pos));
}

wchar_t* strToWchart(char* cStr)
{
	wchar_t* wCharOutput = new wchar_t[1023];
	size_t* sizeOut = new size_t;
	size_t sizeInWords = 256;

	mbstowcs_s(sizeOut, wCharOutput, sizeInWords, cStr, strlen(cStr) + 1);

	return wCharOutput;
}
