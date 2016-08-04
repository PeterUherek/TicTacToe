#pragma once
#include "board.h"
#include "ContextGame.h"
#include <tuple>

class AlgorithmStrategy
{
public:
	virtual ~AlgorithmStrategy() {};

	virtual std::tuple<int, int> ChooseNextSetp() = 0;
	virtual void setPawn(const boost::shared_ptr<Pawn>& pawn) = 0;
	virtual void setGameContext(boost::shared_ptr<ContextGame>& context);

protected:
	boost::shared_ptr<ContextGame> context;
};

