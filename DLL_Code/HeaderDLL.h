#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

struct Person
{
	char* Surname;
	char* Name;
	char* Otchestvo;
	int Age;
};

__declspec(dllimport) void ReadFromFile(struct Person* us);
__declspec(dllimport) void SearchSurname(struct Person* us);
__declspec(dllimport) void WriteToFile(struct Person* current, int countCurrent);
__declspec(dllimport) void SearchSurmameTichinin(struct Person* us);
__declspec(dllimport) void WriteToFileTichinin(struct Person* current, int countCurrent);
typedef int(_cdecl* forReadData)(struct Person*);