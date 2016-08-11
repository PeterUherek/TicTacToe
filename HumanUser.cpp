#include "stdafx.h"
#include <iostream>

#include "InputManager.h"
#include "HumanUser.h"


HumanUser::HumanUser(std::string name) : User(name)  {};
HumanUser::~HumanUser() {};

int HumanUser::Action()
{
	std::cout << std::endl;
	std::cout << this->getName() << std::endl;
	std::cout << "Choose action: " << std::endl;
	std::cout << "Move (1)" << std::endl;
	std::cout << "Undo (2)" << std::endl;
	std::cout << "Redo (3)" << std::endl;
	std::cout << "Save (4)" << std::endl;

	int key = InputManager::GetNumber(1,4);

	return key;
}


bool HumanUser::SaveQuestion() const
{
	std::cout << "Do you want to save game? Your old game will be deleted. (Y/N)" << std::endl;

	char charCollection[] = { 'y', 'n' };
	char key = InputManager::GetChar(charCollection);

	return (key == 'y');
}

std::tuple<int,int> HumanUser::Move()
{	
	std::cout << "Enter coordinates for your turn:" << std::endl;
	int x = InputManager::GetNumber();
	int y = InputManager::GetNumber();
	
	return std::tuple<int, int>(x, y);
}