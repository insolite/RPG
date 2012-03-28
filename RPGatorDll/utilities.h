#pragma once

enum Packet
{
	LogIn = 0,
	LogOut,
	LoggedIn,
	CharacterSpawned
};

enum InitializationType
{
	Editor,
	Server,
	Client
};

#define CELL_SIZE 10

extern "C" __declspec(dllexport) int ReadDir(const char* path, char** &elements, bool directoriesOnly);
extern "C" __declspec(dllexport) void ClearDir(const char* path);

extern "C" __declspec(dllexport) void SetPacketLength(char* packet, int length);
extern "C" __declspec(dllexport) int GetPacketLength(char* packet);
extern "C" __declspec(dllexport) void IncreasePacketLength(char* packet, int length);

extern "C" __declspec(dllexport) void PacketAddString(char* packet, char* str);
extern "C" __declspec(dllexport) void PacketAddInt(char* packet, int n);
extern "C" __declspec(dllexport) void PacketAddShortInt(char* packet, short int n);
extern "C" __declspec(dllexport) void PacketAddByte(char* packet, char n);

extern "C" __declspec(dllexport) char* PacketGetString(char* packet, int pos);
extern "C" __declspec(dllexport) int PacketGetInt(char* packet, int pos);
extern "C" __declspec(dllexport) short int PacketGetShortInt(char* packet, int pos);
extern "C" __declspec(dllexport) char PacketGetByte(char* packet, int pos);

extern "C" __declspec(dllexport) void SetPacketType(char* packet, Packet type);
extern "C" __declspec(dllexport) Packet GetPacketType(char* packet);

extern "C++" __declspec(dllexport) std::vector<SqliteResult> SqliteGetRows(sqlite3* db, char* query);

extern "C++" __declspec(dllexport) int Pix2Index(int pos);
extern "C++" __declspec(dllexport) int Index2Pix(int pos);
extern "C++" __declspec(dllexport) int PixRound(int pos);

extern "C++" __declspec(dllexport) wchar_t* strToWchart(char* cStr);

//extern "C" __declspec(dllexport) int Str2Int(char *str);
//extern "C" __declspec(dllexport) char *Int2Str(int num);
