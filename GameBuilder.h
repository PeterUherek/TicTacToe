#pragma once
#include "game.h"
#include "TicTacToe.h"
#include "User.h"

#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

class GameBuilder
{
public:
	GameBuilder();
	~GameBuilder();

	void createNewGame();
	boost::shared_ptr<IGame> getGame();
	virtual void buildBoard() = 0;
	virtual void buildUser() = 0;
	virtual void buildOptions()= 0;
	virtual void buildLabels()= 0;
	virtual void buildValidator() = 0;

protected:
	boost::shared_ptr<IGame> game;
};

