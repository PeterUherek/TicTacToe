#pragma once
#include <iostream>
#include <string>

#include "GameBuilder.h"
#include "NewGame.h"

class GameDirector {

public:
	GameDirector();
	int SetGame();
	int ConstructGame();
	boost::shared_ptr<IGame> GetGame();

private:

	boost::shared_ptr<GameBuilder> gameBuilder;

};
