#pragma once
#include "User.h"
#include "AlgorithmStrategy.h"


class AIUser :  public User
{

public:
	 AIUser(boost::shared_ptr<AlgorithmStrategy> strategy);
	~AIUser();

	// Inherited via User
	int Action() override;
	std::tuple<int, int> Move() override;
	void setLabel(const boost::shared_ptr<Pawn>& _label) override;
	bool SaveQuestion() const override;

private:
	boost::shared_ptr<AlgorithmStrategy> strategy;

};

