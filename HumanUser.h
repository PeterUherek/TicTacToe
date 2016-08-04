#pragma once
#include "User.h"
#include "Memento.h"

#include <tuple>

class HumanUser : virtual public User
{
public:
	HumanUser(std::string name);
	~HumanUser();

	// Inherited via User
	int Action() override;
	std::tuple<int, int> Move() override;
};

