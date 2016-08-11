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

	// Abstract functions
	virtual int Action() = 0;
	virtual std::tuple<int, int> Move() = 0;
	virtual bool SaveQuestion() const = 0;
	
	// Defined getters
	int GetBestScore();
	int GetLastSocre();
	boost::shared_ptr<Pawn> GetPawn();
	std::string getName() const;

	// Defined setters
	void setScore(const int& _score);
	virtual void setLabel(const boost::shared_ptr<Pawn>& _label);

	// Defined Comparator 
	struct UserComparator {
		bool operator()(const boost::shared_ptr<User>& lhs, const boost::shared_ptr<User>& rhs) const {
			return (lhs->getName() > rhs->getName());
		}
	};

protected:
	std::string name;
	std::vector<int> score = {0};
	boost::shared_ptr<Pawn> label;

};