#include "stdafx.h"
#include <string>
#include <iostream>
#include "User.h"


User::User(std::string name) : name(name), score(0), label(NULL) {}

void User::addScore(const int& _score) { this->score += _score; };
int User::getScore() { return this->score; };
void User::setLabel(const boost::shared_ptr<Pawn>& _label) { label =_label; }

std::string User::getName() { return name;  }
