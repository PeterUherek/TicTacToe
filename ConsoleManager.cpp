#include "stdafx.h"
#include "ConsoleManager.h"
#include <windows.h>


void ConsoleManager::ClearCurrentConsoleLine()
{
	HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord = { 0,0 };
	::SetConsoleCursorPosition(hOutput, coord);

	char buff[] = " ";
	::WriteConsoleA(hOutput, buff, 3, NULL, NULL);
	::SetConsoleCursorPosition(hOutput, {0,8});

}