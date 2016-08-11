#pragma once
#include "game.h"
#include "ContextGame.h"
#include "TicTacToe.h"
#include "User.h"
#include "AIUser.h"

#include <iostream>
#include <boost/shared_ptr.hpp>


class GameBuilder
{
public:
	GameBuilder();
	~GameBuilder();

	void createNewGame();
	boost::shared_ptr<IGame> getGame();
	virtual void buildBoard() = 0;
	virtual void buildUser() = 0;
	virtual void buildOptions() = 0;
	virtual void buildValidator() = 0;
	virtual void BuildBoardState() = 0;
	virtual void BuildOrderOfPlay() = 0;

protected:
	boost::shared_ptr<IGame> game;
	boost::shared_ptr<ContextGame> context;

	// Functions
	boost::shared_ptr<AIUser> createAIPlayer();

	// Template functions 
	template<typename A>
	void VectorShuffle(A& vec)
	{
		std::srand(std::time(0));
		if ((rand() % 2) == 1)
			std::random_shuffle(std::begin(vec), std::end(vec));
	}
};

