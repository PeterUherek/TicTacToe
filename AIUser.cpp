#include "stdafx.h"
#include "AIUser.h"

#include <tuple>


AIUser::AIUser(boost::shared_ptr<AlgorithmStrategy> strategy) : User("AI") 
{
	this->strategy = strategy;
};

AIUser::~AIUser() {};

int AIUser::Action() 
{
	return 1;
}

std::tuple<int, int> AIUser::Move()
{
	return strategy->ChooseNextSetp();
}

void AIUser::setLabel(const boost::shared_ptr<Pawn>& _label)
{
	User::setLabel(_label);
	strategy->setPawn(_label);
}

bool AIUser::SaveQuestion() const
{
	return false;
}

