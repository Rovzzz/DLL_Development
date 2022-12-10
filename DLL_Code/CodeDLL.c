#include "HeaderDLL.h"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{

	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:

		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_THREAD_DETACH:

		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void ReadFromFile(struct Person* us)
{
	system("chcp 1251>nul");
	HANDLE user = CreateFile(L"Users.csv", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (user == INVALID_HANDLE_VALUE) //Проверка неоткрывается ли файл
	{
		MessageBox(NULL, L"Ошибка, нельзя открыть файл", L"Оповещение", MB_OK);
		return;
	}
	DWORD countFileSymbols;
	LPCSTR argumentsFromFile = calloc(4000, sizeof(CHAR));
	if (!ReadFile(user, argumentsFromFile, 4000, &countFileSymbols, NULL)) //Проверка на првильность чтения данных
	{
		MessageBox(NULL, L"Возникла ошибка при чтении данных!", L"Оповещение", MB_OK);
		return 0;
	}
	char* Pars = strtok(argumentsFromFile, ";");
	int CR;
	for (int i = 0; i < 100; i++)
	{
		CR = i;
		us[i].Surname = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Name = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Otchestvo = Pars;
		Pars = strtok(NULL, ";\r\n");
		us[i].Age = atoi(Pars);
		Pars = strtok(NULL, ";\r\n");
	}
	CloseHandle(user);
	SearchSurname(us);
	SearchSurmameTichinin(us);
}
void SearchSurname(struct Person* us)
{
	struct Person* Us = malloc(sizeof(struct Person));
	struct Person* poiskSurName;
	int j = 0, countOfRows = 1;
	char* forComprasion = "Иванов";
	for (int i = 0; i < 100; i++)
	{
		if (strstr(us[i].Surname, forComprasion) != NULL)
		{
			Us[j] = us[i];
			poiskSurName = realloc(Us, (j + 2) * sizeof(struct Person));
			j++;
			Us = poiskSurName;
		}
	}
	WriteToFile(Us, j);
}
void WriteToFile(struct Person* current, int countCurrent)
{
	HANDLE Search = CreateFile(L"UsersSearch.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD countFileSymbols;
	float averageAge = 0;
	char* dataForWritting = calloc(100, sizeof(char));
	for (int i = 0; i < countCurrent; i++)
	{
		sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Surname, current[i].Name, current[i].Otchestvo, current[i].Age);
		WriteFile(Search, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
		averageAge += current[i].Age;
	}
	averageAge /= countCurrent;
	sprintf(dataForWritting, "Средний возраст: %f", averageAge);
	WriteFile(Search, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
	free(dataForWritting);
	CloseHandle(Search);
}
void SearchSurmameTichinin(struct Person* us)
{
	struct Person* Us = malloc(sizeof(struct Person));
	struct Person* NIV;
	int j = 0, countOfRows = 1;
	char* forComprasion = "Тычинин";
	for (int i = 0; i < 100; i++)
	{
		if (strstr(us[i].Surname, forComprasion) != NULL)
		{
			Us[j] = us[i];
			NIV = realloc(Us, (j + 2) * sizeof(struct Person));
			j++;
			Us = NIV;
		}
	}
	WriteToFileTichinin(Us, j);
}
void WriteToFileTichinin(struct Person* current, int countCurrent)
{
	HANDLE SearchTichinin = CreateFile(L"TichininWrite.csv", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD countFileSymbols;
	float averageAge = 0;
	char* dataForWritting = calloc(100, sizeof(char));
	for (int i = 0; i < countCurrent; i++)
	{
		sprintf(dataForWritting, "%s;%s;%s;%d\n", current[i].Surname, current[i].Name, current[i].Otchestvo, current[i].Age);
		WriteFile(SearchTichinin, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
		averageAge += current[i].Age;
	}
	averageAge /= countCurrent;
	sprintf(dataForWritting, "Средний возраст: %f", averageAge);
	WriteFile(SearchTichinin, dataForWritting, strlen(dataForWritting), &countFileSymbols, NULL);
	free(dataForWritting);
	CloseHandle(SearchTichinin);
}