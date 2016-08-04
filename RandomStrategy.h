#pragma once
#include "AlgorithmStrategy.h"


class RandomStrategy : public AlgorithmStrategy
{
public:
	RandomStrategy();
	~RandomStrategy();

	// Inherited via AlgorithmStrategy
	virtual std::tuple<int, int> ChooseNextSetp() override;
	virtual void setPawn(const boost::shared_ptr<Pawn>& pawn) override;

private:
	int GetRandomNum(const int& min, const int& max);

};

