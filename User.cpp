#include "stdafx.h"
#include <string>
#include <iostream>
#include "User.h"


User::User(std::string name) : name(name), score(0), label(NULL) {}

void User::setScore(const int& _score)
{ 
	score.push_back(_score);
};

int User::GetBestScore() 
{ 
	if (score.size() == 0) {
		return 0;
	}
	return *std::max_element(score.begin(), score.end());
};

int User::GetLastSocre()
{
	return score.back();
}
boost::shared_ptr<Pawn> User::GetPawn()
{
	return label;
};


void User::setLabel(const boost::shared_ptr<Pawn>& _label) { label =_label; }

std::string User::getName() const { return name;  }
