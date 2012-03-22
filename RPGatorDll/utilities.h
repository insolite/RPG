#pragma once

extern "C" __declspec(dllexport) int ReadDir(char* path, char** &elements, bool directoriesOnly);
extern "C" __declspec(dllexport) void SetPacketLength(char* packet, int length);
extern "C" __declspec(dllexport) int GetPacketLength(char* packet);
extern "C" __declspec(dllexport) void IncreasePacketLength(char* packet, int length);
extern "C" __declspec(dllexport) void PacketAddString(char* packet, char* str);
extern "C" __declspec(dllexport) void SetPacketType(char* packet, char type);
extern "C" __declspec(dllexport) int SqliteGetRow(sqlite3* db, char* query, std::map<std::string, std::string> &strings, std::map<std::string, int> &integers);
//extern "C" __declspec(dllexport) int Str2Int(char *str);
//extern "C" __declspec(dllexport) char *Int2Str(int num);
