#pragma once

extern "C" __declspec(dllexport) int ReadDir(char* path, char** &elements, bool directoriesOnly);
//extern "C" __declspec(dllexport) int Str2Int(char *str);
//extern "C" __declspec(dllexport) char *Int2Str(int num);
