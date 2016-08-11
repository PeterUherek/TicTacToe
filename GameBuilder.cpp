#include "stdafx.h"
#include "GameBuilder.h"

#include "AlgorithmStrategy.h"
#include "RandomStrategy.h"
#include "HeuristicAlgorithm.h"
#include "AIUser.h"

GameBuilder::GameBuilder() {}
GameBuilder::~GameBuilder() {}

void GameBuilder::createNewGame() 
{ 
	game = boost::shared_ptr<IGame>(new TicTacToe());
	context = boost::shared_ptr<ContextGame>(new ContextGame());
	game->setGameContext(context);
}

boost::shared_ptr<IGame> GameBuilder::getGame() 
{ 
	return game; 
}

boost::shared_ptr<AIUser> GameBuilder::createAIPlayer()
{
	boost::shared_ptr<AIUser> usr;
	boost::shared_ptr<AlgorithmStrategy> strategy;

	if (context->GetOption() == 1)
		strategy = boost::shared_ptr<AlgorithmStrategy>(new RandomStrategy());
	else
		strategy = boost::shared_ptr<AlgorithmStrategy>(new HeuristicAlgorithm(game->getNumberLabelsForWin()));

	strategy->setGameContext(context);

	usr = boost::shared_ptr<AIUser>(new AIUser(strategy));
	return usr;
}