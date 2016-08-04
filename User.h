#pragma once
#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include<limits>

#include "Board.h"
#include "Memento.h"
#include "Pawn.h"

class User {
public:
	User(std::string name);

	virtual int Action() = 0;
	virtual std::tuple<int, int> Move() = 0;
	
	int getScore();
	std::string getName();
	void addScore(const int& _score);
	virtual void setLabel(const boost::shared_ptr<Pawn>& _label);

	struct UserComparator {
		bool operator()(const boost::shared_ptr<User>& lhs, const boost::shared_ptr<User>& rhs) const {
			return (lhs->getName() > rhs->getName());
		}
	};

protected:
	int score;
	std::string name;
	boost::shared_ptr<Pawn> label;

};