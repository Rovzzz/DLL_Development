#pragma once
#include <windows.h>
#include <stdio.h>
#define PATH L"DLL_Code.dll"
typedef int(_cdecl* MyFunc)(struct MyStruct*);
struct MyStruct
{
	char* Surname;
	char* Name;
	char* Otchestvo;
	int Age;
};