#include "stdafx.h"
#include "InputManager.h"

#include <iostream>


int InputManager::GetNumber()
{
	int x = 0;
	while (!(std::cin >> x)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input.  Try again: ";
	}
	return x;
}

int InputManager::GetNumber(const int& downLimit, const int& upLimit)
{
	int key;
	do {
		key = InputManager::GetNumber();
		if (key <= upLimit && downLimit <= key)
			break;

		std::cout << "Input out of the range. Try again: ";
	} while (true);
	return key;
}

char InputManager::GetChar(char *charCollection)
{
	char key;
	do {
		std::cin >> key;
		key = tolower(key);

		char *pch = std::strchr(charCollection, key);
		if (pch != NULL)
			break;

		std::cout << "Invalid input. Try again: ";
	} while (true);

	return key;
}

std::string InputManager::GetString(const int& limit)
{
	std::string str;

	std::cin >> str;
	//std::string strInput = std::string(*str);

	return str;
}
