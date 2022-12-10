#include "HeaderMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hMyDLL;
	if ((hMyDLL = LoadLibrary(PATH)) == NULL) return 1;
	MyFunc myFun = (MyFunc)GetProcAddress(hMyDLL, "ReadFromFile");
	struct MyStruct* us = calloc(5000, sizeof(struct MyStruct));
	myFun(us);

	FreeLibrary(hMyDLL);
	return 0;
}
