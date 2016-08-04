#pragma once
#include <string>

class InputManager
{
public:
	static int GetNumber();
	static int GetNumber(const int& x, const int& y);
	static char GetChar(char* charCollection);
	static std::string GetString(const int& limit);

};

