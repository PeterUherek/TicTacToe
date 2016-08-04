#include "stdafx.h"
#include "GameBuilder.h"


GameBuilder::GameBuilder() {}
GameBuilder::~GameBuilder() {}

void GameBuilder::createNewGame() { game = boost::shared_ptr<IGame>(new TicTacToe()); }
boost::shared_ptr<IGame> GameBuilder::getGame() { return game; }
